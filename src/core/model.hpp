#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <vector>
#include <optional>

// Define data model
struct Entry
{
	std::string service;
	std::string username;
	std::string password;
	std::string notes;
};

// Create a vault of all entries
struct Vault
{
	std::vector<Entry> entries;
};

#endif