#pragma once
#include "clsScreen.h"
#include "clsContact.h"
#include "clsInputValidate.h"
#include <iomanip>


class clsUpdateContactScreen : protected clsScreen
{
private:
	static void _ReadNewContact(clsContact& Contact) {

		cout << "\nEnter a First name : \n";
		Contact.Firstname = clsInputValidate::ReadString();

		cout << "\nEnter a Last name : \n";
		Contact.Lastname = clsInputValidate::ReadString();

		cout << "\nEnter a Email : \n";
		Contact.Email = clsInputValidate::ReadString();

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
	static void ShowUpdateContactScreen() {
	_DrawScreenHeader("\tUpdate Contact Screen");

	cout << "\nEnter a Phone Number : \n";
	string PhoneNumber = clsInputValidate::ReadString();

	while (!clsContact::IsExist(PhoneNumber)) {
		cout << "\nThat number does not exist ,Enter another one: \n";
		PhoneNumber = clsInputValidate::ReadString();
	}

	clsContact Contact = clsContact::Find(PhoneNumber);
	_Print(Contact);
	cout << "\nAre you sure you want to Update that Contact y/n? ";
	char Answer = 'n';
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {
		cout << "\n\nUpdate Contact Info:";
		cout << "\n____________________\n";
		_ReadNewContact(Contact);

		clsContact::enSaveResults SaveResult;
		SaveResult = Contact.Save();

		switch (SaveResult) {
		case clsContact::enSaveResults::svSucceeded:
		{
			cout << "\nContact update Successfully :-)\n";
			_Print(Contact);
			break;
		}
		case clsContact::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError Contact was not saved because it's Empty";
			break;
		}
		case clsContact::enSaveResults::svFaildPhoneNumberExists:
		{
			cout << "\nError Contact was not saved because Phone Number is used!\n";
			break;

		}
		}
		
	}
	else {
		cout << "\nCanceled the update :-)\n";
	}
	
	
	}



};

