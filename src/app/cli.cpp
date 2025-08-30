#include "app/cli.hpp"
#include "core/vault.hpp"
#include "io/file_store.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace
{
	const std::string kDefaultVaultPath = "vault.dev";

	void print_help() // Option menu
	{
		std::cout << "Usage:\n"
					 " pm init                    Create a new (empty) vault\n"
					 " pm add                     Add an entry (prompts for fields)\n"
					 " pm list                    List all services\n"
					 " pm show <service>          Show username/password/notes for a service\n"
					 " pm help                    Show this help\n";
	}

	// Read a full line
	std::string prompt(const std::string &label, bool allow_empty = true)
	{
		std::cout << label;
		std::string s;
		std::getline(std::cin, s);
		while (!allow_empty && s.empty())
		{
			std::cout << "(required)" << label;
			std::getline(std::cin, s);
		}
		return s;
	}

	bool file_exists(const std::string &path)
	{
		namespace fs = std::filesystem;
		std::error_code ec;
		return fs::exists(path, ec);
	}

	// Initialize vault file (encryption next)
	bool do_init(const std::string &path)
	{
		if (file_exists(path))
		{
			std::cout << "Vault already exists as '" << path << "'.\n";
			return false;
		}
		Vault v;
		std::string err;
		if (!store::saveVault(path, v, err))
		{
			std::cerr << "Error creating vault: " << err << "\n";
			return false;
		}
		std::cout << "Created new vault at '" << path << "'.\n";
		return true;
	}

	// Add new entry
	bool do_add(const std::string &path)
	{
		std::string err;
		Vault v;
		if (!store::loadVault(path, v, err))
		{
			std::cerr << "Error loading vault: " << err << "\n";
			return false;
		}

		std::cout << "Adding a new entry (temporary plaintext in Step 1 - DO NOT USE REAL PASSWORD)\n";
		std::string service = prompt("Service: ", /*allow_empty=*/false);
		std::string username = prompt("Username: ", /*allow_empty=*/false);
		std::string password = prompt("Password: ", /*allow_empty*/ false);
		std::string notes = prompt("Notes (optional): ");

		core::addEntry(v, Entry{service, username, password, notes});

		if (!store::saveVault(path, v, err))
		{
			std::cerr << "Error saving vault: " << err << "\n";
			return false;
		}
		std::cout << "Entry added for service '" << service << "'.\n";
		return true;
	}

	// List all services available in file
	bool do_list(const std::string &path)
	{
		std::string err;
		Vault v;
		if (!store::loadVault(path, v, err))
		{
			std::cerr << "Error loading vault: " << err << "\n";
			return false;
		}

		const auto entries = core::listEntries(v);
		if (entries.empty())
		{
			std::cout << "(no entries)\n";
			return true;
		}

		std::cout << "Services:\n";
		for (const auto &e : entries) // List services of all entries
		{
			std::cout << "  - " << e.service << "\n";
		}
		return true;
	}

	// Show all data of chosen service
	bool do_show(const std::string &path, const std::string &service)
	{
		std::string err;
		Vault v;
		if (!store::loadVault(path, v, err))
		{
			std::cerr << "Error loading vault: " << err << "\n";
			return false;
		}

		auto found = core::findByService(v, service);
		if (!found)
		{
			std::cout << "Service '" << service << "' not found.\n";
			return false;
		}

		const auto &e = *found;
		std::cout << "Service:  " << e.service << "\n"
				  << "Username: " << e.username << "\n"
				  << "Password: " << e.password << "\n"
				  << "Notes:    " << e.notes << "\n";
		return true;
	}
}

int run_cli(int argc, char **argv)
{
	std::cin.clear();

	if (argc < 2)
	{
		print_help();
		return 0;
	}

	std::string cmd = argv[1];

	if (cmd == "help" || cmd == "-h" || cmd == "--help")
	{
		print_help();
		return 0;
	}
	if (cmd == "init") // These are the command strings (ex. pm init)
	{
		return do_init(kDefaultVaultPath) ? 0 : 1;
	}
	if (cmd == "add")
	{
		return do_add(kDefaultVaultPath) ? 0 : 1;
	}
	if (cmd == "list")
	{
		return do_list(kDefaultVaultPath) ? 0 : 1;
	}
	if (cmd == "show")
	{
		if (argc < 3)
		{
			std::cerr << "Usage: pm show <service>\n";
			return 1;
		}
		return do_show(kDefaultVaultPath, argv[2]) ? 0 : 1;
	}

	std::cerr << "Unknown command: " << cmd << "\n\n";
	print_help();
	return 1;
}