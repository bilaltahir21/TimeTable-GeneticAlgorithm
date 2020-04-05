#pragma once
#include <random>
#include "HashMap.h"

// Data from "registration.data"
int noOfCourses;
int studentCount;

// Data from "general.info"
int totalExamDays;
int examSlotsPerDay;

// Data from "capacity.info"
int examSlotsPerTime;
// Supposed from the available rooms

// Matrix of total student registration
std::vector<std::vector<int>> registrationData;
// Room capacity data
std::vector<int> roomCapacity;
// Total room capacity
int totalRoomCapacity;

// Map to check if an exam is already scheduled
std::map<int, bool> scheduledExam;
// Array to store number of exams that can be
// held in a day
std::vector<int> examsInDay;
std::vector<int> shadow;
int courseCount = 0;
// Function to evaluate these exams
inline void assignExams() {
	for (int i = 0; i < noOfCourses; i++) {
		shadow.push_back(i);
	}
	std::shuffle(shadow.begin(), shadow.end(), std::mt19937(std::random_device()()));
	for (int i = 0; i < noOfCourses; i++) {
		scheduledExam[i] = false;
	}
	examsInDay.resize(totalExamDays);
	const int lowerBound = int(floor(noOfCourses / totalExamDays));
	for (int i = 0; i<totalExamDays; i++) { examsInDay.at(i) = lowerBound; }
	int examsLeft = noOfCourses - (lowerBound * totalExamDays);
	for (int i = examsInDay.size() - 1; i >= 0 && examsLeft != 0; i--) {
		examsInDay.at(i)++;
		examsLeft--;
	}
}


// Maximum fitness a gene can have
constexpr int MAX_FITNESS = 100000;
int MAX_FITNESS_DNA;

/*
  Seems like I'm insane, don't worry.
  It is worth it because we will have
  to generate small tables in each iteration
  and they take more time than this single
  pass calculation for every student. Of course
  it will take space but not much like processing.
 */
HashMap* studentsData_student=nullptr;
HashMap* studentsData_course=nullptr;

inline void populateStudentsData_student() {
	if (!studentsData_student) { studentsData_student = new HashMap(studentCount); }
	for (int i = 0; i < studentCount; i++) {
		for (int j = 0; j < noOfCourses; j++) {
			if (registrationData.at(i).at(j) == 1) { studentsData_student->hash.at(i).push_back(j); }
		}
	}
}

inline void populateStudentsData_course() {
	if (!studentsData_course) { studentsData_course = new HashMap(noOfCourses); }
	for (int i = 0; i < studentCount; i++) {
		for (int j = 0; j < noOfCourses; j++) {
			if (registrationData.at(i).at(j) == 1) { studentsData_course->hash.at(j).push_back(i); }
		}
	}
}

inline void whatRoomCapacity() {
	totalRoomCapacity = 0;
	for (int i : roomCapacity) { totalRoomCapacity = totalRoomCapacity + i; }
}

// Estimating max fitness of DNA
inline void doMaxDNAFitness() { MAX_FITNESS_DNA = MAX_FITNESS * totalExamDays; }

// For taking transpose of registration data matrix
inline std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> registrationData) {
	std::vector<std::vector<int>> data(studentCount);
	for (int i = 0; i < studentCount; i++) {
		for (int j = 0; j < noOfCourses; j++) { data.at(i).push_back(registrationData[j][i]); }
	}
	return data;
}
