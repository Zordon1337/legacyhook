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
	std::unordered_map<int, WeaponSkin> weapon_skins;   // mapping of weapon id -> WeaponSkin
	std::unordered_map<std::string, int> paintkit_ids;  // mapping of paintkit name -> paintkit id

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
		// Step 1: Find weapon by ID
		auto weaponIt = weapon_skins.find(weaponId);
		if (weaponIt != weapon_skins.end()) {
			std::string paintkitName = weaponIt->second.paintkit_name;

			// Step 2: Find paintkit ID based on paintkit name
			auto paintkitIt = paintkit_ids.find(paintkitName);
			if (paintkitIt != paintkit_ids.end()) {
				return paintkitIt->second; // Found paintkit ID
			}
			else {
				std::cerr << "Paintkit name not found: " << paintkitName << std::endl;
				return -1; // Return an error code if paintkit is not found
			}
		}
		else {
			std::cerr << "Weapon with ID " << weaponId << " not found." << std::endl;
			return -1; // Return an error code if weapon is not found
		}
	}
};