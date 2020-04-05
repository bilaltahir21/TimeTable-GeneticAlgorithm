#pragma once
#include "2. DNA.h"
// This file contains the local search by using successor functions
// And improve already available solution stuck on local maximum by
// considering this local maximum as a base.
inline void localSearch(DNA& fittest) {
	DNA fit = fittest;
	DNA temp = fittest;
	while (fit.fitnessOfDNA != MAX_FITNESS_DNA) {
		temp = fit;
		for (int gene = 0; gene < int(temp.genes.size()); gene++) {
			temp.genes.at(gene).externallyRandomize();
			temp.guageDNAfitness();
			if (temp.fitnessOfDNA > fit.fitnessOfDNA) { fit = temp; }
			else { temp = fit; }
		}
	}
	fittest = fit;
}
