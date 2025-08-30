#ifndef FILE_STORE_HPP
#define FILE_STORE_HPP

#include "core/model.hpp"

#include <string>

namespace store
{
	bool saveVault(const std::string &path, const Vault &v, std::string &err);
	bool loadVault(const std::string &path, Vault &v, std::string &err);
}

#endif