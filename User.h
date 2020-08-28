#pragma once
#define RED "\033[31m"
#define RESET "\033[0m"
#include <string>
#include <iostream>
#include <iomanip>
class User
{
private:
	std::string name;
	float ammount_spent;
	float balance;
	float due;
public:
	User(std::string name) : name(name), ammount_spent(0), balance(0), due(0) {};
	void add_expense(float value);
	void add_due(float value);
	float get_ammout_spent();
	std::string get_name();
	void compute_balance();
	friend bool operator==(const User u1, const User u2);
	friend std::ostream& operator<<(std::ostream& out, const User &user);
};

