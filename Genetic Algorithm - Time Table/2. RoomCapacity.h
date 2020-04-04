#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline std::vector<int> roomCapacityData(const std::string& fileName) {
	//input stream for filing
	std::ifstream inputFile(fileName);

	//if file is available
	if (inputFile.fail()) {
		std::cout << "File: " << fileName << " -> loading error!\n";
		exit(EXIT_FAILURE);
	}

	// We will return this vector
	std::vector<int> roomCapacity;

	std::string input, token;
	std::vector<std::string> storage;

	/*
	 *Here we're using a stringStream to act as a stream
	 *which is used in the function std::getline()
	 *and the vector is being used to store the tokens,
	 *we made.
	 */

	while (std::getline(inputFile, input)) {
		if (!input.empty() && input != " ") {
			std::istringstream ss(input);

#pragma loop( ivdep )
#pragma loop( hint_parallel(4))
			while (std::getline(ss, token, ' ')) { storage.push_back(token); }

			for (auto& i : storage) { roomCapacity.push_back(atoi(i.c_str())); }

			//managing vector space
			storage.clear();
		}
	}

	inputFile.close();

	return roomCapacity;
}
