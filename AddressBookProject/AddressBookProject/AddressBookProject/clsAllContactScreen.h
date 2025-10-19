#pragma once
#include "clsScreen.h"
#include "clsContact.h"
#include <iomanip>
class clsAllContactScreen : protected clsScreen
{
private:
    static void _PrintContactRecordLine(clsContact Contact) {

        cout << "| " << setw(40) << left << Contact.FullName();
        cout << "| " << setw(15) << left << Contact.Phone;
        cout << "| " << setw(25) << left << Contact.Email;
        

    }

public:
	static void ShowAllContactScreen() {
		_DrawScreenHeader("\tAll Contact Screen");

		vector <clsContact> vContacts;
		vContacts = clsContact::GetContactsList();

        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(15) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        
        
        cout << "\n_______________________________________________________";
        cout << "_____________________________________________________________\n" << endl;

        if (vContacts.size() == 0)
            cout << "\t\t\t\tNo Contacts Available In the System!";

        else

            for (const clsContact& Contact : vContacts)
            {

                _PrintContactRecordLine(Contact);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_____________________________________________________________\n" << endl;

	}
};

