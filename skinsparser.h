#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include "json.hpp"

struct WeaponSkin {
	int id;
	std::string name;
	std::string paintkit_name;
};

class Root {
public:
	std::unordered_map<int, WeaponSkin> weapon_skins;   
	std::unordered_map<std::string, int> paintkit_ids;  

	void parseJson(const std::string& jsonData) {
		json j = json::parse(jsonData);

		// Parsing weapon_skins
		for (const auto& item : j["weapon_skins"]) {
			WeaponSkin skin;
			skin.id = item["id"];
			skin.name = item["name"];
			skin.paintkit_name = item["paintkit_name"];
			weapon_skins[skin.id] = skin;
		}

		// Parsing paintkit_ids
		for (const auto& item : j["paintkit_ids"].items()) {
			paintkit_ids[item.key()] = item.value();
		}
	}

	int getPaintkitIdForWeapon(int weaponId) {
		auto weaponIt = weapon_skins.find(weaponId);
		if (weaponIt != weapon_skins.end()) {
			std::string paintkitName = weaponIt->second.paintkit_name;

			auto paintkitIt = paintkit_ids.find(paintkitName);
			if (paintkitIt != paintkit_ids.end()) {
				return paintkitIt->second;
			}
			else {
				std::cerr << "Paintkit name not found: " << paintkitName << std::endl;
				return -1; 
			}
		}
		else {
			std::cerr << "Weapon with ID " << weaponId << " not found." << std::endl;
			return -1;
		}
	}
};