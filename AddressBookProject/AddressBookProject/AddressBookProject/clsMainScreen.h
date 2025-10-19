#pragma once

#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsAllContactScreen.h"
#include "clsAddNewContactScreen.h"
#include "clsUpdateContactScreen.h"
#include "clsDeleteContactScreen.h"
#include "clsFindContactScreen.h"
#include <iomanip>


class clsMainScreen : protected clsScreen
{

private:
	enum enMainContactMenueOptions {
		eAllContact = 1, eAddNewContact = 2, eUpdateContact = 3,
		eDeleteContact = 4 , eFindContact = 5, eExit = 6
	};

	static short _ReadMainMenueOption() {
		short Number;

		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		Number = clsInputValidate::ReadShortNumberBetween(1, 6, "Choose what do you want to do? [1 to 6]? ");

		return Number;
	}

	static void _GoBackToMainMenue() {

		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Contact Menue...\n\n";
		system("pause>0");

		ShowMainMenueScreen();
	}

	static void _ShowAllContactScreen() {
		clsAllContactScreen::ShowAllContactScreen();
	}

	static void _ShowAddNewContactScreen() {
		clsAddNewContactScreen::ShowAddNewContactScreen();
	}

	static void _ShowUpdateContactScreen() {
		clsUpdateContactScreen::ShowUpdateContactScreen();
	}

	static void _ShowDeleteContactScreen() {
		clsDeleteContactScreen::ShowDeleteContactScreen();
	}
	
	static void _ShowFindContactScreen() {
		clsFindContactScreen::ShowFindContactScreen();
	}

	static void _PerformMainContactMenueOption(enMainContactMenueOptions ContactMenueOption) {
		switch (ContactMenueOption) {
		case enMainContactMenueOptions::eAllContact: {
			system("cls");
			_ShowAllContactScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainContactMenueOptions::eAddNewContact: {
			system("cls");
			_ShowAddNewContactScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainContactMenueOptions::eUpdateContact: {
			system("cls");
			_ShowUpdateContactScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainContactMenueOptions::eDeleteContact: {
			system("cls");
			_ShowDeleteContactScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainContactMenueOptions::eFindContact: {
			system("cls");
			_ShowFindContactScreen();
			_GoBackToMainMenue();
			break;
		}
		case enMainContactMenueOptions::eExit: {
			
		}
		
		}
	}


public:
	static void ShowMainMenueScreen() {
		system("cls");
		_DrawScreenHeader("\t  Address Book Menu Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show All Contact List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Contact.\n";
		cout << setw(37) << left << "" << "\t[3] Update Contact.\n";
		cout << setw(37) << left << "" << "\t[4] delete Contact.\n";
		cout << setw(37) << left << "" << "\t[5] Search Contact.\n";
		cout << setw(37) << left << "" << "\t[6] Exit.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainContactMenueOption((enMainContactMenueOptions)_ReadMainMenueOption());
	}
};

