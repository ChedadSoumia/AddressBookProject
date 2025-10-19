#pragma once
#include "clsString.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class clsContact 
{

private:
	string _Firstname;
	string _Lastname;
	string _Phone;
	string _Email;
	bool MarkForDelete = false;

	enum enMode{EmptyMode = 0, UpdateMode = 1,AddNewMode = 3};
	enMode _Mode;

	static clsContact _ConvertLineToObject(string Line , string Seperetor = "#//#") {
		vector <string> vContacts;
		vContacts = clsString::Split(Line,Seperetor);
		return clsContact(enMode::UpdateMode,vContacts[0],vContacts[1],vContacts[2],vContacts[3]);
	}

	static clsContact _GetEmptyContactObject() {
		return clsContact(enMode::EmptyMode,"","","","");
	}

	static vector <clsContact> _LoadContactsDataFromFile() {

		vector <clsContact> vContacts;

		fstream MyFile;
		MyFile.open("Contacts.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {
				clsContact Contact = _ConvertLineToObject(Line);
				vContacts.push_back(Contact);
			}
		}

		return vContacts;

	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Contacts.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static string _ConvertObjectToLine(clsContact Contact, string Seperator = "#//#") {

		string sContactLine = "";
		sContactLine += Contact.Firstname + Seperator;
		sContactLine += Contact.Lastname + Seperator;
		sContactLine += Contact.Phone + Seperator;
		sContactLine += Contact.Email;

		return sContactLine;
	}

	void _AddNewContact() {
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	static void _SaveContactDataToFile(vector <clsContact> vContacts) {
		fstream MyFile;
		MyFile.open("Contacts.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsContact& C : vContacts)
			{
				if (C.MarkForDelete == false)
				{
					DataLine = _ConvertObjectToLine(C);
					MyFile << DataLine << endl;
				}

			}

			MyFile.close();

		}
	}

	void _Update(){
		vector <clsContact> _vContact = _LoadContactsDataFromFile();

		for (clsContact &Contact : _vContact) {
			if (Contact.Phone == _Phone) {

				Contact = *this;
				break;
			}
		}
		_SaveContactDataToFile(_vContact);
	}

public:
	clsContact(enMode Mode,string Firstname,string Lastname,string Phone,string Email){
	
		_Mode = Mode;
		_Firstname = Firstname;
		_Lastname = Lastname;
		_Phone = Phone;
		_Email = Email;

	}

	string GetFirstname() {
		return _Firstname;
	}
	void SetFirstname(string Firstname) {
		_Firstname = Firstname;
	}
	__declspec(property(get = GetFirstname , put = SetFirstname)) string Firstname;

	string GetLastname() {
		return _Lastname;
	}
	void SetLastname(string Lastname) {
		_Lastname = Lastname;
	}
	__declspec(property(get = GetLastname, put = SetLastname)) string Lastname;


	string GetPhone() {
		return _Phone;
	}
	void SetPhone(string Phone) {
		_Phone = Phone;
	}
	__declspec(property(get = GetPhone, put = SetPhone)) string Phone;


	string GetEmail() {
		return _Email;
	}
	void SetEmail(string Email) {
		_Email = Email;
	}
	__declspec(property(get = GetEmail, put = SetEmail)) string Email;

	string FullName(){
		return _Firstname + " " + _Lastname;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	static clsContact Find(string PhoneNumber) {

		fstream MyFile;
		MyFile.open("Contacts.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {
				clsContact Contact = _ConvertLineToObject(Line);
				if (Contact.Phone == PhoneNumber) {
					MyFile.close();
					return Contact;
				}
			}
			MyFile.close();

		}
		return _GetEmptyContactObject();
	}

	static clsContact GetNewContactObject(string PhoneNumber) {
		return clsContact(enMode::AddNewMode , "","", PhoneNumber,"");
	}

	static bool IsExist(string PhoneNumber) {
		clsContact Contact = clsContact::Find(PhoneNumber);
		return (!Contact.IsEmpty());
	}

	static vector <clsContact> GetContactsList() {
		return _LoadContactsDataFromFile();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildPhoneNumberExists = 2 };


	enSaveResults Save() {

		switch (_Mode) {
		case enMode::EmptyMode: {
			return enSaveResults::svFaildEmptyObject;
		}
		case enMode::UpdateMode: {
			_Update();
			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode: {
			if (IsExist(Phone)) {
				return enSaveResults::svFaildPhoneNumberExists;
			}
			else {
				_AddNewContact();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
				break;
			}
		}
		}

	}

	bool Delete() {
		vector <clsContact> _vContacts = _LoadContactsDataFromFile();
		for (clsContact& Contact : _vContacts) {
			if (Contact.Phone == Phone) {
				Contact.MarkForDelete = true;
				break;
			}
		}
		_SaveContactDataToFile(_vContacts);
		*this = _GetEmptyContactObject();
		return true;

	}
};

