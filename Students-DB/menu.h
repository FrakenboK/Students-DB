#pragma once

string currentPath = ".\\Students";

#include <conio.h>
#include <windows.h>

#include "printers.h"
#include "directory_functions.h"
#include "object_functions.h"
#include "menu_models.h"
#include "input_menus.h"

class SelectDirParam : public virtual SelectParamMenuReturnModel {
public:
	SelectDirParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetNewObjectParams();
	}
};

class SelectStudentParam : public virtual SelectParamMenuReturnModel {
public:
	SelectStudentParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetParsedStudentsFromDir(currentPath);
	}
};

class InfoMenu {
public:
	static void Run(string message) {
		system(CLEAR_COMMAND);
		PrintOneParam(message);
		int key = 0;
		while (true) {
			key = _getch();
			if (key == ESC || key == ENTER) {
				break;
			}
		}
	}
};

class DefaultSelectionMenuWithButtons : public virtual MainChooseMenu {
protected:
	virtual List<string>& ParseParams() = 0;
	virtual void NextMenuRun(string selectedParam) = 0;
	virtual void OnCreate() = 0;
	virtual void OnDelete() = 0;

	void OnEnter() override {
		if (IsIdenticalParam(selectedOption, identicalButtonsNumber)) {
			NextMenuRun(backupParams[selectedOption]);
		}
		else {
			if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
				OnCreate();
			}
			else {
				OnDelete();
			}

		}
	}
};

class SemesterSelectionMenu : public virtual MainChooseMenu {
public:
	SemesterSelectionMenu(string param) {
		header = "Select semester marks for " + param;
	}
private:
	string header;
	List<string>& ParseParams() override {
		List<string>* params = new List<string>;
		for (int i = 1; i < 10; ++i) {
			params->Append("Semester " + to_string(i));
		}
		return *params;
	}
	void Printer() override {
		PrintParams(params,backupParams,header);
	}
};



class StudentsParamsMenu : public virtual MainChooseMenu{
public:
	Student student;
	StudentsParamsMenu() {
		object = "students's paramenters";
		student = Read(currentPath);
	}
private:
	string header = "Select students's paramenters";
	List<string>& ParseParams() override {
		return *GetStudentsParams(currentPath, student);
	}
	void Printer() override {
		PrintStudent(params, backupParams, header);
	}
	virtual void OnEnter() override {
		switch (selectedOption) {
		case 0: {
			string newSurname = InputLetterOnlyMenu::Run("Enter the student's surname: ", student.GetSurname(), DEFAULT_STRING_LENGTH - 1);
			while (newSurname == "") {
				newSurname = InputLetterOnlyMenu::Run("Enter the correct surname: ", student.GetSurname(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newSurname != ESCAPE_STRING) {
				DeleteStudentFile(currentPath);
				student.SetSurname(newSurname);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 1: {
			string newName = InputLetterOnlyMenu::Run("Enter the student's name: ", student.GetName(), DEFAULT_STRING_LENGTH - 1);
			while (newName == "") {
				newName = InputLetterOnlyMenu::Run("Enter the correct name: ", student.GetName(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newName != ESCAPE_STRING) {
				DeleteStudentFile(currentPath);
				student.SetName(newName);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 2: {
			string newPatronymic = InputLetterOnlyMenu::Run("Enter the student's name: ", student.GetPatronymic(), DEFAULT_STRING_LENGTH - 1);
			while (newPatronymic == "") {
				newPatronymic = InputLetterOnlyMenu::Run("Enter the correct name: ", student.GetPatronymic(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newPatronymic != ESCAPE_STRING) {
				DeleteStudentFile(currentPath);
				student.SetPatronymic(newPatronymic);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 3: { // Validation!
			string newInstitute = InputMenu::Run("Enter the student's institute: ", student.GetInstitute(), DEFAULT_STRING_LENGTH - 1);
			while (newInstitute == "") {
				newInstitute = InputMenu::Run("Enter the correct institute: ", student.GetInstitute(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newInstitute != ESCAPE_STRING) {
				student.SetInstitute(newInstitute);
			}
			break;
		}
		case 4: {
			string newDepartment = InputMenu::Run("Enter the student's department: ", student.GetDepartment(), DEFAULT_STRING_LENGTH - 1);
			while (newDepartment == "") {
				newDepartment = InputMenu::Run("Enter the correct department: ", student.GetDepartment(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newDepartment != ESCAPE_STRING) {
				student.SetDepartment(newDepartment);
			}
			break;
		}
		case 5: { // Validation!
			string newGroup = InputMenu::Run("Enter the student's group: ", student.GetGroup(), DEFAULT_STRING_LENGTH - 1);
			while (newGroup == "") {
				newGroup = InputMenu::Run("Enter the correct group: ", student.GetGroup(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newGroup != ESCAPE_STRING) {
				student.SetGroup(newGroup);
			}
			break;
		}
		case 6: {
			string newRecordBookNumber = InputMenu::Run("Enter the student's record book number: ", student.GetRecordBookNumber(), RECORD_BOOK_STR_LENGTH - 2);
			while (newRecordBookNumber == "") {
				newRecordBookNumber = InputMenu::Run("Enter the correct record book number: ", student.GetRecordBookNumber(), RECORD_BOOK_STR_LENGTH - 2);
			}
			if (newRecordBookNumber != ESCAPE_STRING) {
				student.SetRecordBookNumber(newRecordBookNumber);
			}
			break;
		}
		case 7: {
			string newGender = InputLetterOnlyMenu::Run("Enter the student's gender: ", student.GetGender(), 1);
			while (newGender == "") {
				newGender = InputLetterOnlyMenu::Run("Enter the correct gender: ", student.GetGender(), 1);
			}
			if (newGender != ESCAPE_STRING) {
				student.SetGender(newGender);
			}
			break;
		}
		case 8: {
			string newAdmissionYear = InputNumberOnlyMenu::Run("Enter the student's admission year: ", student.GetStringAdmissionYear(), 4);
			while (newAdmissionYear == "") {
				newAdmissionYear = InputNumberOnlyMenu::Run("Enter the correct admission year: ", student.GetStringAdmissionYear(), 4);
			}
			if (newAdmissionYear != ESCAPE_STRING) {
				student.SetAdmissionYear(stoi(newAdmissionYear));
			}
			break;
		}
		case 9: {
			string day = InputNumberOnlyMenu::Run("Enter the student's day of birthday: ", "", 2);
			while (day == "") {
				day = InputNumberOnlyMenu::Run("Please, enter correct day of birthday: ", "", 2);
			}
			if (day != ESCAPE_STRING) {
				string month = InputNumberOnlyMenu::Run("Enter the student's month of birthday: ", "", 2);
				while (month == "") {
					month = InputNumberOnlyMenu::Run("Please, enter correct month of birthday: ", "", 2);
				}
				if (month != ESCAPE_STRING) {
					string year = InputNumberOnlyMenu::Run("Enter the student's year of birthday: ", "", 4);
					while (year == "") {
						year = InputNumberOnlyMenu::Run("Please, enter correct year of birthday: ", "", 4);
					}
					if (year != ESCAPE_STRING) {
						Date birthday = {stoi(day),stoi(month), stoi(year)};
						student.SetBirthday(birthday);
					}
				}
			}
			break;
		}
		case 10: {
			SemesterSelectionMenu semesters {student.GetSurname() + " " + student.GetName() + " " + student.GetPatronymic()};
			semesters.Run();
			break;
		}
		}
		Write(student);
		ResetParams();
	}
};

class StudentSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	StudentSelectionMenu() {
		object = "student";
	}
private:
	void Printer() override {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetGroup(), identicalButtonsNumber);
	}
	List<string>& ParseParams() override {
		return *GetParsedStudentsFromDirWithExtraButtons(currentPath, object);
	}

	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + GetFilenameFromParsedStudent(selectedParam);
		StudentsParamsMenu paramsMenu{};
		paramsMenu.Run();
		RestoreCurrentPath();
		ResetParams();
	}

	void OnCreate() override{
		string surname = InputLetterOnlyMenu::Run("Enter the student's surname: ", "", DEFAULT_STRING_LENGTH - 1);
		while (surname == "") {
			surname = InputLetterOnlyMenu::Run("Please, enter some surname: ", "", DEFAULT_STRING_LENGTH - 1);
		}
		if (surname != ESCAPE_STRING) {
			string name = InputLetterOnlyMenu::Run("Enter the student's name: ", "", DEFAULT_STRING_LENGTH - 1);
			while (name == "") {
				name = InputLetterOnlyMenu::Run("Please, enter some name: ", "", DEFAULT_STRING_LENGTH - 1);
			}
			if (name != ESCAPE_STRING) {
				string patronymic = InputLetterOnlyMenu::Run("Enter the student's patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				while (patronymic == "") {
					patronymic = InputLetterOnlyMenu::Run("Please, enter some patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				}
				if (patronymic != ESCAPE_STRING) {
					if (IsStudentExists(surname + " " + name + " " + patronymic, currentPath)) {
						InfoMenu::Run("This student is already in the database");
					} else {
						Student student;
						student.SetName(name);
						student.SetSurname(surname);
						student.SetPatronymic(patronymic);
						student.SetGroup(GetGroup());
						student.SetInstitute(GetInstitute());
						Write(student);
						InfoMenu::Run("Student successfully added to the database!");
						ResetParams();
					}
				}
			}
		}
	}

	void OnDelete() override {
		if (identicalButtonsNumber > 0) {
			SelectStudentParam delMenu = SelectStudentParam(object, "Select " + object + " to delete");
			string selectedObject = delMenu.Run();
			if (selectedObject != ESCAPE_STRING) {
				DeleteStudentFile(currentPath + "\\" + GetFilenameFromParsedStudent(selectedObject));

				ResetParams();

				InfoMenu::Run("Successfully deleted " + object + "!");
			}
		}
		else {
			InfoMenu::Run("Nothing to delete!");
		}
	}
};

class StudentsOptionsSelectionMenu : public virtual MainChooseMenu {
public:
	StudentsOptionsSelectionMenu() {
		object = "option";
	}
private:
	string header = "Select option to view students";
	List<string>& ParseParams() override {
		List<string>* clearParams = new List<string>;
		clearParams->Append("Print all students");
		clearParams->Append("Divide students by grades (Variant 73)");
		return *clearParams;
	}
	void Printer() {
		PrintParams(params, backupParams, header);
	}
	virtual void OnEnter() override {
		if (selectedOption == 0) {
			StudentSelectionMenu student;
			student.Run();
		}
		else {
			InfoMenu::Run("Doesen't work now!");
		}
	}
};


class GroupSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	GroupSelectionMenu() {
		object = "group";
	}
private:
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetInstitute(), identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + selectedParam;
		StudentsOptionsSelectionMenu option{};
		option.Run();
		RestoreCurrentPath();

	}
	List<string>& ParseParams() override {
		return *GetNewDirParamsWithExtraParams(currentPath, object);
	}
	void OnCreate() { 
		string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = InputMenu::Run("Enter correct " + object + " name : ", "", 30);
		}

		if (createdObject != ESCAPE_STRING) {
			if (!IsDirectoryExists(createdObject, currentPath)) {
				MakeDirectory(currentPath + "\\" + createdObject);

				ResetParams();

				InfoMenu::Run("Successfully added " + object + "!");

			}
			else {
				InfoMenu::Run("Group already created!");
			}
		}
	}
	void OnDelete() override { 
		if (identicalButtonsNumber > 0) {
			SelectDirParam delMenu = SelectDirParam(object, "Select " + object + " to delete");
			string selectedObject = delMenu.Run();

			if (selectedObject != ESCAPE_STRING) {
				DeleteDirectory(currentPath + "\\" + selectedObject);

				ResetParams();

				InfoMenu::Run("Successfully deleted " + object + "!");
			}
		}
		else {
			InfoMenu::Run("Nothing to delete!");
		}
	}
};



class InstituteSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	InstituteSelectionMenu() {
		object = "institute";
	}
private:
	void Printer() override {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from DB", identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + selectedParam;
		GroupSelectionMenu groupMenu;
		groupMenu.Run();
		RestoreCurrentPath();
	}

	List<string>& ParseParams() override {
		return *GetNewDirParamsWithExtraParams(currentPath, object);
	}
	void OnCreate() { // Default (we can make custom)
		string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = InputMenu::Run("Enter correct " + object + " name : ", "", 30);
		}

		if (createdObject != ESCAPE_STRING) {
			if (!IsDirectoryExists(createdObject, currentPath)) {
				MakeDirectory(currentPath + "\\" + createdObject);

				ResetParams();

				InfoMenu::Run("Successfully added " + object + "!");

			}
			else {
				InfoMenu::Run("Institute already created!");
			}
		}
	}
	void OnDelete() override { // Default (we can make custom)
		if (identicalButtonsNumber > 0) {
			SelectDirParam delMenu = SelectDirParam(object, "Select " + object + " to delete");
			string selectedObject = delMenu.Run();
			if (selectedObject != ESCAPE_STRING) {
				DeleteDirectory(currentPath + "\\" + selectedObject);

				ResetParams();

				InfoMenu::Run("Successfully deleted " + object + "!");
			}
		}
		else {
			InfoMenu::Run("Nothing to delete!");
		}
	}
};
