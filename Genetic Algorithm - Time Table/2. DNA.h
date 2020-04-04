#pragma once
#include <vector>
#include "1. Member.h"
#include "4. GeneralMember.h"

class DNA {
public:
	int fitnessOfDNA;
	
	std::vector<Member> genes;
	
	DNA() = default;

	DNA(const int numberOfDays) {
		genes.resize(numberOfDays);
		for (int i = 0; i < int(genes.size()); i++) {
			courseCount = 0;
			genes[i] = Member(examSlotsPerDay, noOfCourses,i);
		}
		for (int i = 0; i < int(genes.size()); i++) {
			courseCount = 0;
			genes[i].randomize();
			genes[i].fitness = 0;
		}
	}

	void randomize() { for (int i = 0; i < int(genes.size()); i++) { genes[i].randomize(); } }

	void guageDNAfitness() {
		fitnessOfDNA = 0;
		for (int i = 0; i < int(genes.size()); i++) {
			this->genes[i].guageFitness(MAX_FITNESS);
			fitnessOfDNA = fitnessOfDNA + this->genes[i].fitness;
		}
	}
};
