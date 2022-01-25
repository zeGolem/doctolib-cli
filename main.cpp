#include "doctolib/doctolib_api.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

template <typename T> std::string get_name(T const &);

template <> std::string get_name(doctolib::speciality const &speciality)
{
	return speciality.name;
}

template <> std::string get_name(doctolib::place const &place)
{
	return place.label;
}

template <typename T>
T const pick(std::vector<T> const &list, std::string const &selection_name)
{
	if (list.size() == 1) return list[0];
	std::cout << '\n';
	uint16_t i = 1;
	for (auto const &item : list) {
		std::cout << i << ". " << get_name(item) << '\n';
		++i;
	}

	std::cout << "Select a " << selection_name
	          << " (type the associated number) >> ";

	uint16_t selected_index;
	std::cin >> selected_index;
	return list[selected_index - 1];
}

void find_specialists(std::string const &speciality_query,
                      std::string const &place_query)
{
	doctolib::doctolib_api api("https://www.doctolib.fr");

	auto const speciality =
	    pick(api.get_specialities(speciality_query), "speciality");
	auto const place = pick(api.get_places(place_query), "place");

	std::cout << "Searching for '" << speciality.name << "' in '"
	          << place.description << "'...\n\n";

	auto const doctors = api.get_doctors_for_speciality(speciality, place);
	for (auto const &doc : doctors) {
		std::cout << doc.name_with_title << '\n';
		std::cout << doc.address << ", " << doc.city << " (" << doc.zipcode
		          << ")" << '\n';
		std::cout << "https://www.doctolib.fr" << doc.link << '\n';
		std::cout << "====================\n";
	}
}

void find_profile(std::string const &profile_query)
{
	doctolib::doctolib_api api("https://www.doctolib.fr");

	auto const profiles = api.get_profiles(profile_query);
	for (auto const &profile : profiles) {
		std::cout << profile.name_with_title << " -- " << profile.kind << '\n';
		std::cout << profile.city << '\n';
		std::cout << "https://www.doctolib.fr" << profile.link << '\n';
		std::cout << "====================\n";
	}
}

int main(int argc, char **argv)
{
	if (argc < 1) return -1;

	if (std::string(argv[1]) == "find-specialist") {
		if (argc < 3) return -1;
		find_specialists(argv[2], argv[3]);
	} else if (std::string(argv[1]) == "find-profile") {
		if (argc < 2) return -1;
		find_profile(argv[2]);
	}
}
