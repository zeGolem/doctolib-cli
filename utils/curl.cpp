#include "curl.hpp"

namespace curl
{
static size_t writer_append(char *data,
                            size_t size,
                            size_t nmemb,
                            std::string *buffer)
{
	if (!buffer) return 0;
	buffer->append(data, size * nmemb);
	return size * nmemb;
}

std::string const get(std::string const &url)
{
	std::string buffer;
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer_append);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return buffer;
}
} // namespace curl
