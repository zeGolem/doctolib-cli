#include "doctolib_api.hpp"
#include "../utils/curl.hpp"
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

namespace doctolib
{
std::string const doctolib_api::get(std::string const &url)
{
	// TODO: Check time since last request to avoid spamming the API
	return curl::get(m_base_url + url);
}

std::vector<place> const doctolib_api::get_places(
    std::string const &search_term)
{
	auto const raw_data = get("/patient_app/place_autocomplete.json?query=" +
	                          curl::url_encode(search_term));
	auto const json = nlohmann::json::parse(raw_data);
	std::vector<place> places;
	for (auto const &place_json : json)
		places.push_back(place::from_json(place_json));
	return places;
}

std::vector<speciality> const doctolib_api::get_specialities(
    std::string const &search_term)
{
	auto const raw_data = get("/api/searchbar/autocomplete.json?search=" +
	                          curl::url_encode(search_term));
	auto const json = nlohmann::json::parse(raw_data);
	std::vector<speciality> specialities;
	for (auto const &specialty_json : json.at("specialities"))
		specialities.push_back(speciality::from_json(specialty_json));
	return specialities;
}

std::vector<profile> const doctolib_api::get_profiles(
    const std::string &search_term)
{
	auto const raw_data = get("/api/searchbar/autocomplete.json?search=" +
	                          curl::url_encode(search_term));
	auto const json = nlohmann::json::parse(raw_data);
	std::vector<profile> profiles;
	for (auto const &profile_json : json["profiles"])
		profiles.push_back(profile::from_json(profile_json));
	return profiles;
}

std::vector<doctor> const doctolib_api::get_doctors_for_speciality(
    speciality const &speciality, place const &place)
{
	std::string real_link;
	{
		auto const &speciality_slug = speciality.slug;
		auto const &place_id = place.place_id;
		auto const raw_data = get(
		    "/patient_app/search_doctors.json?speciality=" + speciality_slug +
		    "&place_id=" + place_id);
		real_link =
		    nlohmann::json::parse(raw_data).at("path").get<std::string>() +
		    ".json";
	}
	auto const raw_data = get(real_link);
	auto const json = nlohmann::json::parse(raw_data);
	std::vector<doctor> doctors;
	for (auto const &doc_json : json["data"]["doctors"])
		doctors.push_back(doctor::from_json(doc_json));
	return doctors;
}

full_profile const doctolib_api::get_full_profile(const profile &profile)
{
	auto const raw_data = get(profile.link + ".json");
	auto const json = nlohmann::json::parse(raw_data);
	return full_profile::from_json(json["data"]["profile"]);
}
} // namespace doctolib
