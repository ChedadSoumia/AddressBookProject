#pragma once
#include "clsScreen.h"
#include "clsContact.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewContactScreen : protected clsScreen
{
private :
	static void _ReadNewContact(clsContact &NewContact) {

		cout << "\nEnter a First name : \n";
		NewContact.Firstname = clsInputValidate::ReadString();

		cout << "\nEnter a Last name : \n";
		NewContact.Lastname = clsInputValidate::ReadString();

		cout << "\nEnter a Email : \n";
		NewContact.Email = clsInputValidate::ReadString();

	}
	static void _Print(clsContact Contact) {
		cout << "\nContact Info:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Contact.FullName();
		cout << "\nPhone       : " << Contact.Phone;
		cout << "\nEmail       : " << Contact.Email;
		cout << "\n___________________\n";
	}


public:

	static void ShowAddNewContactScreen() {

		_DrawScreenHeader("\tAdd New Contact Screen");

		cout << "\nEnter a Phone Number : \n";
		string PhoneNumber = clsInputValidate::ReadString();

		while (clsContact::IsExist(PhoneNumber)) {
			cout << "\nThat number is already exist ,Chose another one: \n";
			PhoneNumber = clsInputValidate::ReadString();
		}

		clsContact NewContact = clsContact::GetNewContactObject(PhoneNumber);

		_ReadNewContact(NewContact);

		clsContact::enSaveResults SaveResult;
		SaveResult = NewContact.Save();

		switch (SaveResult) {
		case clsContact::enSaveResults::svSucceeded: {
			cout << "\nPhone Number Added Successfully :-)\n";
			_Print(NewContact);
			break;
		}case clsContact::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError Contact was not saved because it's Empty";
			break;
		}
		case clsContact::enSaveResults::svFaildPhoneNumberExists:
		{
			cout << "\nError Contact was not saved because Username is used!\n";
			break;

		}
		}


	}


};

