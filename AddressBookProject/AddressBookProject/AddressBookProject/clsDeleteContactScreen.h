#pragma once
#include "clsScreen.h"
#include "clsContact.h"
#include "clsInputValidate.h"

class clsDeleteContactScreen : protected clsScreen
{
private:
	static void _Print(clsContact Contact) {
		cout << "\nContact Info:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Contact.FullName();
		cout << "\nPhone       : " << Contact.Phone;
		cout << "\nEmail       : " << Contact.Email;
		cout << "\n___________________\n";
	}



public:
	static void ShowDeleteContactScreen() {
		_DrawScreenHeader("\tFind Contact Screen");
		cout << "\nEnter a Phone Number : \n";
		string PhoneNumber = clsInputValidate::ReadString();

		while (!clsContact::IsExist(PhoneNumber)) {
			cout << "\nThat number does not exist ,Enter another one: \n";
			PhoneNumber = clsInputValidate::ReadString();
		}

		clsContact Contact = clsContact::Find(PhoneNumber);
		_Print(Contact);


		cout << "\nAre you sure you want to delete that Contact y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			if (Contact.Delete()) {
				cout << "\nContact Deleted Successfully :-)\n";

				_Print(Contact);
			}
			else {
				cout << "\nError Contact Was not Deleted\n";
			}


		}
		else {
			cout << "\nCanceled the Delete :-)\n";
		}

	}

};

