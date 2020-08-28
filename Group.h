#pragma once
#define BLUE "\033[34m"
#define RED "\033[31m"
#define RESET "\033[0m"
#include "User.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <conio.h>

class Group
{
private:
	std::vector<User*> members;
	std::string name;
	std::string filename_users_db;
	std::string filename_expenses_db;
public:
	Group(std::string name, std::string filename_users_db="users.csv", std::string filename_expenses_db="expenses.csv") : name(name), filename_users_db(filename_users_db), filename_expenses_db(filename_expenses_db) {};
	void add_user(User* new_user);
	void add_user(std::string name);
	friend std::ostream& operator<<(std::ostream& out, const Group& group);
	void add_expense(std::string name, float ammount, int who_paid_id, std::vector<bool> involved);
	void load_data();
	void list_members(std::vector<std::string> chosen);
	void list_members(std::vector<bool> chosen);
	std::string get_name_of_member(int i);
	int get_number_of_members() { return members.size(); };
	void sava_data_user(std::string name);
	void save_data_expense(std::string name, float ammount, int who_paid_id, std::vector<bool> involved);
	void print_expenses();
};

