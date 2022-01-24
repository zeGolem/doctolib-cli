#pragma once

#include <cstdint>
#include <ctime>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "../json.hpp"

namespace doctolib
{

struct place {
	std::string description;
	std::string place_id;
	std::string label;
	std::optional<std::string> address;
	std::string city;
	std::string country;

	static place from_json(nlohmann::json const &j)
	{
		place p{};
		p.description = j.at("description").get<std::string>();
		p.place_id = j.at("place_id").get<std::string>();
		p.label = j.at("label").get<std::string>();
		if (!j.at("address").is_null())
			p.address = j.at("address").get<std::string>();
		p.city = j.at("city").get<std::string>();
		p.country = j.at("country").get<std::string>();
		return p;
	}
};

struct profile {
	std::string city;
	uint16_t value;
	std::string name_with_title;
	std::string kind;
	std::string link;

	static profile from_json(nlohmann::json const &j)
	{
		profile p{};
		p.city = j.at("city").get<std::string>();
		p.value = j.at("value").get<uint16_t>();
		p.name_with_title = j.at("name_with_title").get<std::string>();
		p.kind = j.at("kind").get<std::string>();
		p.link = j.at("link").get<std::string>();
		return p;
	}
};

struct speciality {
	uint16_t value;
	std::string slug;
	std::string name;

	static speciality from_json(nlohmann::json const &j)
	{
		speciality s{};
		s.value = j.at("value").get<uint16_t>();
		s.slug = j.at("slug").get<std::string>();
		s.name = j.at("name").get<std::string>();
		return s;
	}
};

struct position {
	double lat;
	double lng;

	static position from_json(nlohmann::json const &j)
	{
		position p{};
		p.lat = j.at("lat").get<double>();
		p.lng = j.at("lng").get<double>();
		return p;
	}
};

struct doctor {
	uint16_t id;
	bool is_directory;
	std::string address;
	std::string city;
	std::string zipcode;
	uint16_t practice_id;
	std::string link;
	int64_t profile_id;
	bool exact_match;
	std::string name_with_title;
	position position;
	bool telehealth;

	static doctor from_json(nlohmann::json const &j)
	{
		doctor d{};
		d.id = j.at("id").get<uint16_t>();
		d.is_directory = j.at("is_directory").get<bool>();
		d.address = j.at("address").get<std::string>();
		d.city = j.at("city").get<std::string>();
		d.zipcode = j.at("zipcode").get<std::string>();
		d.practice_id = j.at("practice_id").get<uint16_t>();
		d.link = j.at("link").get<std::string>();
		d.profile_id = j.at("profile_id").get<int64_t>();
		d.exact_match = j.at("exact_match").get<bool>();
		d.name_with_title = j.at("name_with_title").get<std::string>();
		d.position = position::from_json(j.at("position"));
		d.telehealth = j.at("telehealth").get<bool>();
		return d;
	}
};

class doctolib_api
{
  private:
	// TODO: Use this to wait between requests
	std::time_t m_last_request_time = 0;
	std::string const m_base_url;

	std::string const get(std::string const &url);

  public:
	doctolib_api(std::string const base_url) : m_base_url(base_url) {}
	~doctolib_api() {}

	std::vector<place> const get_places(std::string const &search_term);
	std::vector<speciality> const get_specialities(
	    std::string const &search_term);
	std::vector<profile> const get_profiles(std::string const &search_term);

	std::vector<doctor> const get_doctors_for_speciality(
	    speciality const &speciality, place const &place);
};
} // namespace doctolib
