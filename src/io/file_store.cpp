#include "io/file_store.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace store
{

	bool saveVault(const std::string &path, const Vault &v, std::string &err)
	{
		try
		{
			// Write to a temp file
			std::string tempPath = path + ".tmp";
			std::ofstream out(tempPath, std::ios::trunc); // ios::trunc to rewrite current file (for future reference)
			if (!out.is_open())
			{
				err = "Failed to open file for writing: " + tempPath;
				return false;
			}

			for (Entry e : v.entries)
			{ // Write output to file from vault entries
				out << "service: " << e.service << "\n"
					<< "username: " << e.username << "\n"
					<< "password: " << e.password << "\n"
					<< "notes: " << e.notes << "\n"
					<< "---\n";
			}
			out.close();

			// Replace old file
			fs::rename(tempPath, path);
			return true;
		}
		catch (const std::exception &ex)
		{
			err = ex.what();
			return false;
		}
	}

	bool loadVault(const std::string &path, Vault &v, std::string &err)
	{
		v.entries.clear(); // Clear current vault

		std::ifstream in(path);
		if (!in.is_open())
		{
			// Return empty vault if file doesn't exist
			return true;
		}

		try
		{
			std::string line;
			Entry current;
			while (std::getline(in, line))
			{
				if (line.rfind("service:", 0) == 0)
				{
					current.service = line.substr(9);
				}
				else if (line.rfind("username:", 0) == 0)
				{
					current.username = line.substr(10);
				}
				else if (line.rfind("password:", 0) == 0)
				{
					current.password = line.substr(10);
				}
				else if (line.rfind("notes:", 0) == 0)
				{
					current.notes = line.substr(7);
				}
				else if (line == "---")
				{
					v.entries.emplace_back(current); // Place new entry
					current = Entry{};				 // Reset current
				}
			}

			// If file doesn't end with "---"
			if (!current.service.empty() || !current.username.empty() || !current.password.empty() || !current.notes.empty())
			{
				v.entries.emplace_back(current);
			}

			return true;
		}
		catch (const std::exception &ex)
		{
			err = ex.what();
			return false;
		}
	}

} // namespace store