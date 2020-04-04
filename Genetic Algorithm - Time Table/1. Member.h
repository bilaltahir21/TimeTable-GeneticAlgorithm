#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <vector>
#include "4. GeneralMember.h"
#include "HashMap.h"

class Member {
public:
	int fitness;
	int whatDayIsIt;
	std::vector<int> object;
	int slotsPerDay;
	int noOfCourses;
	/*
	 * It is made on number of slots
	 * Each slot has the course which
	 * has exam on that slot. This aids
	 * in handling available room capacity
	 * and finding the number of clashes
	 * for each student
	 */
	HashMap* map_course=nullptr;
	HashMap* map_slot=nullptr;

	Member() = default;

	Member(const int slotsPerDay, const int courses,int day) {
		/*
		 * Representing the gene in the form of a 1D
		 * array with array index representing the course
		 * while the value at an index represents the slot
		 * from the available slots
		 */
		object.resize(courses);
		for (int i = 0; i < int(object.size()); i++) { object.at(i) = -1; }
		this->noOfCourses = courses;
		this->slotsPerDay = slotsPerDay;
		this->whatDayIsIt = day;
		randomize();
		whatRoomCapacity();
	}


	// This number represents the times in which
	// the total room capacity in increased
	int capacityExceeded;
	void checkCapacityLimits() {
		capacityExceeded = 0;
		for (int i = 0; i < int(map_course->hash.size()); i++) {
			if (int(map_course->hash.at(i).size()) > int(roomCapacity.size())) { capacityExceeded++; }
		}
	}

	int clashCount;
	void checkClashes() {
		clashCount = 0;
		for (int slot = 0; slot < int(map_slot->hash.size()); slot++) {
			// Courses in this selected slot
			std::vector<int> courses(map_slot->hash.at(slot).size());
			for (int i = 0; i < int(map_slot->hash.at(slot).size()); i++) {
				courses.push_back(map_slot->hash.at(slot).at(i));
			}
			if (studentsData_course) {
				// To store all the students
				std::vector<int> registeredStudents;
				for (int i = 0; i < int(courses.size()); i++) {
					for (int j = 0; j < int(studentsData_course->hash.at(courses.at(i)).size()); j++) {
						registeredStudents.push_back(studentsData_course->hash.at(courses.at(i)).at(j));
					}
				}
				// Now, count the repeating students (Clashes)
				std::map<int, int> clashCheck;
				for (auto const& c : registeredStudents) { clashCheck[c]++; }
				// Now counting clashes
				for (auto const& student : clashCheck) {
					if (student.second > 1) { clashCount = clashCount + student.second; }
				}
			}
		}
	}

	void randomize() {
#pragma warning( disable : 4244 )
		// Emptying all the slots in the array by putting -1 everywhere
		for (int i = 0; i < int(object.size()); i++) { this->object.at(i) = -1; }
		// Here is the code for randomization
		srand(time(NULL));
		// Handling that there should not be the same exam multiple days. And the exams come by randomization
		for (int i = 0; i < examsInDay.at(whatDayIsIt); i++) {
			this->object.at(shadow[courseCount++]) = (rand() % slotsPerDay);
			scheduledExam[shadow[courseCount++]] = true;
		}

		/* Prepare data for pre-processing */
		// Storing course at index
		if (!map_course) {
			map_course = nullptr;
			map_course = new HashMap(slotsPerDay);
		}
		else { map_course = new HashMap(slotsPerDay); }
		for (int i = 0; i < int(object.size()); i++) {
			if (object.at(i) != -1) { map_course->hash.at(object.at(i)).push_back(i); }
		}

		// Storing slot at index
		if (!map_slot) {
			map_slot = nullptr;
			map_slot = new HashMap(noOfCourses);
		}
		else { map_slot = new HashMap(noOfCourses); }
		for (int i = 0; i < int(object.size()); i++) {
			if (object.at(i) != -1) { map_slot->hash.at(i).push_back(object.at(i)); }
		}
	}

	void externallyRandomize() {
		for (int& i : object) {
			if(i !=-1) {
				i = (rand() % slotsPerDay);
			}
		}
		
		/* Prepare data for pre-processing */
		// Storing course at index
		if (!map_course) {
			map_course = nullptr;
			map_course = new HashMap(slotsPerDay);
		}
		else { map_course = new HashMap(slotsPerDay); }
		for (int i = 0; i < int(object.size()); i++) {
			if (object.at(i) != -1) { map_course->hash.at(object.at(i)).push_back(i); }
		}

		// Storing slot at index
		if (!map_slot) {
			map_slot = nullptr;
			map_slot = new HashMap(noOfCourses);
		}
		else { map_slot = new HashMap(noOfCourses); }
		for (int i = 0; i < int(object.size()); i++) {
			if (object.at(i) != -1) { map_slot->hash.at(i).push_back(object.at(i)); }
		}
	}

	void guageFitness(int maxFitness) {
		checkCapacityLimits();
		checkClashes();
		this->fitness = maxFitness - ((capacityExceeded * 500) + (clashCount + 250));
	}
};
