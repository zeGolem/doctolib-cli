#pragma once

#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

namespace curl
{
std::string const get(std::string const &url);
} // namespace curl
