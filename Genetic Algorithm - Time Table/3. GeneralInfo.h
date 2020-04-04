#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline void generalInfoData(const std::string& fileName, int& examDays, int& slotsPerDay) {
	std::ifstream inputFile(fileName);

	std::string input, token;
	std::vector<std::string> storage;
	if (inputFile.is_open()) {
		while (getline(inputFile, input)) {
			std::istringstream ss(input);
#pragma loop( ivdep )
#pragma loop( hint_parallel(4))
			while (std::getline(ss, token, ' ')) { storage.push_back(token); }
			// Total days for exam
			examDays = atoi(storage[0].c_str());
			slotsPerDay = atoi(storage[1].c_str());
		}
		inputFile.close();
	}
	else { std::cout << "File: " << fileName << " -> not found!"; }
}
