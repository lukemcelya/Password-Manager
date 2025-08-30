#ifndef VAULT_HPP
#define VAULT_HPP

#include "core/model.hpp"

#include <string>
#include <optional>

namespace core
{
	void addEntry(Vault &v, Entry e);
	std::vector<Entry> listEntries(const Vault &v);
	std::optional<Entry> findByService(const Vault &v, const std::string &service);
	bool updateEntry(Vault &v, const Entry &e);
	bool removeByService(Vault &v, const std::string &service);
}

#endif