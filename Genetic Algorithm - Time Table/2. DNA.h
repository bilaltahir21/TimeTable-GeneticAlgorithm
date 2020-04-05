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

// Condition to make a valid timetable
int stu = 0;
void threeExamsCondition() {
	stu = 0;
	// Dummy timetable to test the condition of three
	// exams in the same day
	DNA dummy(totalExamDays);
	for (int i = 0; i < int(dummy.genes.size()); i++) {
		std::vector<int> heldExams;
		for (int h = 0; h < int(dummy.genes.at(i).object.size()); h++) {
			if (dummy.genes.at(i).object.at(h) != -1) { heldExams.push_back(h); }
		}
		std::vector<int> students;
		for (int x = 0; x < int(heldExams.size()); x++) {
			for (int y = 0; y < studentsData_course->hash.at(heldExams.at(x)).size(); y++) {
				students.push_back(studentsData_course->hash.at(heldExams.at(x)).at(y));
			}
		}
		// Now, count the repeating students (Clashes)
		std::map<int, int> check;
		for (auto const& c : students) { check[c]++; }
		// Now counting clashes
		for (auto const& student : check) { if (student.second > 3) { stu = stu + student.second; } }
	}
	if (stu > 0) { assignExams(); }
}

void threeExamsWrapper() {
	while (stu>0) {
		threeExamsWrapper();
	}
}