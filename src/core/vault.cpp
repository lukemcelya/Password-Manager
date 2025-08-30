#include "core/vault.hpp"

namespace core
{
	void addEntry(Vault &v, Entry e)
	{
		v.entries.emplace_back(e); // Place current entry into the vault
	}

	std::vector<Entry> listEntries(const Vault &v)
	{
		return v.entries;
	}

	std::optional<Entry> findByService(const Vault &v, const std::string &service)
	{
		for (Entry e : v.entries)
		{
			if (e.service == service)
			{
				return e; // return entry when service found
			}
		}
		return std::nullopt; // not found
	}

	bool updateEntry(Vault &v, const Entry &e)
	{
		for (Entry &entry : v.entries)
		{
			if (entry.service == e.service)
			{
				entry = e; // overwrite new data
				return true;
			}
		}
		return false; // not found
	}

	bool removeByService(Vault &v, const std::string &service)
	{
		for (auto it = v.entries.begin(); it != v.entries.end(); ++it)
		{
			if (it->service == service)
			{
				v.entries.erase(it);
				return true;
			}
		}
		return false;
	}
} // namespace core