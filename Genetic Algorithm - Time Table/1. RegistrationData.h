#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::vector<int>> studentRegistrationData(const std::string& fileName) {
	//input stream for filing
	std::ifstream ile(fileName);

	//if file is available
	if (ile.fail()) {
		std::cout << "File: " << fileName << " -> loading error!\n";
		exit(EXIT_FAILURE);
	}

	int lineCount = 0;
	std::string line;
	while (std::getline(ile, line)) { lineCount++; }
	ile.close();
	// We will return this vector
	std::vector<std::vector<int>> registrationData(lineCount);

	std::ifstream inputFile(fileName);

	std::string input, token;
	std::vector<std::string> storage;

	/*
	 *Here we're using a stringStream to act as a stream
	 *which is used in the function std::getline()
	 *and the vector is being used to store the tokens,
	 *we made.
	 */

	int subject = 0;
	while (std::getline(inputFile, input)) {
		if (!input.empty() && input != " ") {
			std::istringstream ss(input);

#pragma loop( ivdep )
#pragma loop( hint_parallel(4))
			while (std::getline(ss, token, '\t')) { storage.push_back(token); }

			for (int i = 0; i < storage.size(); i++) { registrationData[subject].push_back(atoi(storage[i].c_str())); }

			//managing vector space
			storage.clear();
			subject++;
		}
	}

	noOfCourses = int(registrationData.size());
	studentCount = int(registrationData.at(0).size());

	inputFile.close();

	std::vector<std::vector<int>> data = std::vector<std::vector<int>>(registrationData);
	registrationData.clear();
	registrationData = transpose(data);
	data.clear();
	
	return registrationData;
}
