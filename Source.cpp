# include "Group.h"
#include <Windows.h>
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define LOGO1 "\t        _____        _ _ _    __           ___"
#define LOGO2 "\t       / ____|      | (_) |   \\ \\         / (_)"
#define LOGO3 "\t       | (___  _ __ | |_| |_   \\ \\  / \\  / / _ ___  ___ "
#define LOGO4 "\t       \\___ \\ | '_ \\| | | __|   \\ \\/   \\/ / | / __|/ _ \\ "
#define LOGO5 "\t        ____) | |_) | | | |_     \\   /\\  /  | \\__ \\  __/  "
#define LOGO6 "\t       |_____/|.__/ |_|_|\\__|     \\ /  \\/   |_|___/\\___| " 
#define LOGO7 "\t              | | "
#define LOGO8 "\t              |_| "
void print_menu()
{
	system("CLS");
	
	std::cout << LOGO1 << std::endl;
	std::cout << LOGO2 << std::endl;
	std::cout << LOGO3 << std::endl;
	std::cout << LOGO4 << std::endl;
	std::cout << LOGO5 << std::endl;
	std::cout << LOGO6 << std::endl;
	std::cout << LOGO7 << std::endl;
	std::cout << LOGO8 << std::endl;

	std::cout << "\t------------------------------------------------------------" << std::endl;
	std::cout << "\t|                   1. Add a new member                    |" << std::endl;
	std::cout << "\t|                  2. Add a new expense                    |" << std::endl;
	std::cout << "\t|                  3. Show group balance                   |" << std::endl;
	std::cout << "\t|                    4. List expenses                      |" << std::endl;
	std::cout << "\t------------------------------------------------------------" << std::endl;
	std::cout << "\t|                         0. Exit                          |" << std::endl;
	std::cout << "\t------------------------------------------------------------" << std::endl;
}



void add_expense_menu(Group group)
{
	std::string name;
	float ammount;
	int choice = -1;
	int who_paid_id;
	std::vector<bool> involved;
	for (int i = 0; i < group.get_number_of_members(); i++)
		involved.push_back(false);
	system("CLS");
	std::cout << "Enter a name of new expense: ";
	std::cin >> name;
	std::cout << "Enter the ammount of the expense: ";
	std::cin >> ammount;

	bool fine_input = false;
	while (!fine_input)
	{
		system("CLS");
		std::cout << "Choose who paid: " << std::endl;
		group.list_members(involved);
		std::cout << "----------------------" << std::endl;
		std::cout << "0. CANCEL" << std::endl;
		std::cin >> who_paid_id;
		if (who_paid_id == 0) return;
		if (who_paid_id > 0 && who_paid_id < involved.size() + 1)
		{
			who_paid_id--;
			fine_input = true;
		}
	}
	while (choice)
	{
		system("CLS");
		std::cout << "Choose who is involved: ";
		std::cout << BLUE << "involved " << RESET;
		std::cout << "not involved" << std::endl;
		group.list_members(involved);
		std::cout << "----------------------" << std::endl;
		std::cout << "0. SAVE AND EXIT" << std::endl;
		std::cin >> choice;
		if (choice > 0 && choice < involved.size() + 1)
		{
			if (involved[choice - 1]) involved[choice - 1] = false;
			else involved[choice - 1] = true;
		}
	}
	group.add_expense(name, ammount, who_paid_id, involved);
	group.save_data_expense(name, ammount, who_paid_id, involved);
}

void add_user_menu(Group& group)
{
	std::string name_of_new_user;
	std::cout << "Enter the name of a new user: ";
	std::cin >> name_of_new_user;
	group.add_user(name_of_new_user);
	group.sava_data_user(name_of_new_user);
}

int main()
{
	Group LD("LD");
	LD.load_data();
	int choice = -1;
	while (choice != 0)
	{
		print_menu();
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			add_user_menu(LD);
			break;
		case 2:
			add_expense_menu(LD);
			break;
		case 3:
			system("CLS");
			std::cout << LD;
			system("PAUSE");
			break;
		case 4:
			system("CLS");
			LD.print_expenses();
			system("PAUSE");
			break;
		case 0:
			std::cout <<  "EXIT!";
			break;
		default:
			std::cout << "Wrong value!";
			break;

		}
	}
	return 0;

}