#include "User.h"

void User::add_expense(float value)
{
	this->ammount_spent += value;
}

void User::add_due(float value)
{
	this->due += value;
}

float User::get_ammout_spent()
{
	return this->ammount_spent;
}

std::string User::get_name()
{
	return name;
}

void User::compute_balance()
{
	this->balance = ammount_spent - due;
}

bool operator==(const User u1, const User u2)
{
	return (u1.ammount_spent == u2.ammount_spent && u1.due == u2.due && u1.name == u2.name);
}

std::ostream& operator<<(std::ostream& out, const User& user)
{
	out << "\t" << std::setw(15) << user.name << std::setw(10) << std::fixed << std::setprecision(2) << user.ammount_spent
		<< std::setw(10) << user.due;
	if (user.balance < 0) out << RED << std::setw(10) << std::right  << user.balance << RESET;
	else out << std::right << std::setw(10) << user.balance;
	return out;
}
