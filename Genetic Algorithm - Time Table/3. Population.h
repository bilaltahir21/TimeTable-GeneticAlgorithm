#pragma once
#include <algorithm>
#include <vector>
#include "2. DNA.h"

class Population {
public:
	std::vector<DNA> members;

	// First we will have to define the density of population
	// then we will be able to make it work by giving it random DNA.
	// Default value  for population is 5k
	Population() {
		// Every single DNA comes randomized and
		// fitness set to 0
		members = std::vector<DNA>(5000);
		for (int i = 0; i < 5000; i++) { members.at(i) = DNA(totalExamDays); }
	}

	explicit Population(const int population) {
		members = std::vector<DNA>(population);
		for (int i = 0; i < population; i++) {
			courseCount = 0;
			members.at(i) = DNA(totalExamDays);
		}
	}
};

// Sorting the population according to fitness values from highest to lowest 
inline void sortPopulation(Population& population) {
	// Just using the STL sorting
	std::sort(population.members.begin(), population.members.end(),
	          [](DNA& first, DNA& second) { return first.fitnessOfDNA > second.fitnessOfDNA; });
}

inline std::vector<DNA> eligibleParents(Population& population, const int count) {
	std::vector<DNA> parents;
	std::vector<int> chosen;
#pragma warning( disable : 4244 )
	srand(time(NULL));
	for (int i = 0; i < int(2 * count); i++) {
		int point = rand() % (2 * count);
		// Check if parent is already selected 
		while (chosen.end() != std::find(chosen.begin(), chosen.end(), point)) { point = rand() % (2 * count); }
		chosen.push_back(point);
		parents.push_back(population.members.at(point));
	}
	// Sorting them from high to low
	std::sort(parents.begin(), parents.end(),
	          [](DNA& first, DNA& second) { return first.fitnessOfDNA > second.fitnessOfDNA; });
	return parents;
}

inline void doMating(std::vector<DNA>& parents, const int mutationRate, int totalFitness) {
#pragma warning( disable : 4244 )
	srand(time(NULL));
	int sizeOfDNA = int(parents.at(0).genes.size());
	for (int i = 0; i < parents.size(); i = i + 2) {
		const int howMuch = int(rand()) % int(parents.at(i).genes.size());
		for (int j = 0; j < howMuch; j++) {
			std::swap(parents.at(i).genes.at(j), parents.at(i + 1).genes.at(j));
		}

		// Doing mutation according to above parameters
		if (rand() % 1000 < mutationRate) {
			parents.at(i).genes.at(rand() % parents.at(i).genes.size()).externallyRandomize();
		}
	}
	// Sorting them from high to low
	std::sort(parents.begin(), parents.end(),
	          [](DNA& first, DNA& second) { return first.fitnessOfDNA > second.fitnessOfDNA; });
}
