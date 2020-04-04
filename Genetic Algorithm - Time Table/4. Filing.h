#pragma once
#include "1. RegistrationData.h"
#include "2. RoomCapacity.h"
#include "3. GeneralInfo.h"
#include "4. GeneralMember.h"
// Just one function to load all the files
// and setting their values in "GeneralMember.h"

void doFiling(const std::string& registrationDataFile, const std::string& roomCapacityFile, const std::string& generalInfoFile) {
	/******************************************************************************/
	registrationData = studentRegistrationData(registrationDataFile);
	populateStudentsData_student();
	populateStudentsData_course();
	/******************************************************************************/
	roomCapacity = roomCapacityData(roomCapacityFile);
	examSlotsPerTime = int(roomCapacity.size());
	/******************************************************************************/
	generalInfoData(generalInfoFile, totalExamDays, examSlotsPerDay);
	/******************************************************************************/
	doMaxDNAFitness();
}
