#include "Group.h"

void Group::add_user(User* new_user)
{
	members.push_back(new_user);
	std::ofstream file;
	file.open(filename_users_db, std::ios::app);
	file << new_user->get_name() << std::endl;
	file.close();
}

void Group::add_user(std::string name)
{
	User* p;
	p = new User(name);
	members.push_back(p);
}


void Group::add_expense(std::string name, float ammount, int who_paid_id, std::vector<bool> involved)
{
	int how_many_involved=0;
	for (int i = 0; i < (int)involved.size(); i++)
		if (involved[i]) how_many_involved++;
	members[who_paid_id]->add_expense(ammount);
	float due_value = ammount / how_many_involved;
	for (int i = 0; i < (int)involved.size(); i++)
	{
		if (involved[i])
		{
			members[i]->add_due(due_value);
			members[i]->compute_balance();
		}
	}
}

void Group::load_data()
{
	// loading members
	std::string line;
	std::ifstream users_file;
	users_file.open(filename_users_db);
	std::cout << "Adding users: " << std::endl;
	while (getline(users_file, line))
	{
		std::cout << "-" << line << std::endl;;
		add_user(line);
	}
	std::cout << std::endl;
	// loading expenses
	std::ifstream expenses_file;
	std::string word;
	std::vector<std::string> words;
	std::cout << "Loading expenses: " << std::endl ;
	expenses_file.open(filename_expenses_db);
	if (expenses_file.good())
	{
		while (getline(expenses_file, line))
		{
			std::stringstream s(line);
			while (getline(s, word, ','))
			{
				words.push_back(word);
			}

			std::cout << words[0] << " " << words[1] << " who paid: " << words[2] << " involve:  ";
			for (int i = 3; i < (int)words.size(); i++)
				std::cout << words[i];
			std::cout << std::endl;
			std::vector<bool> involved;
			for (int i = 0; i < (int)words.size() - 3; i++)
			{
				if (words[i+3] == "1")
				{
					involved.push_back(true);
				}
				else
				{
					involved.push_back(false);
				}
			}
			add_expense(words[0], std::stof(words[1]), std::stoi(words[2]), involved);
			words.clear();
		}
	}
}


void Group::list_members(std::vector<std::string> chosen)
{
	bool exists;
	for (int i = 0; i < (int)members.size(); i++)
	{
		exists = false;
		for (int j = 0; j < (int)chosen.size(); j++)
		{
			if (chosen[j] == (members[i])->get_name())
			{
				exists = true;
			}
		}
		if (exists)
		{
			std::cout << "\033[34m" << i+1 << ". " << members[i]->get_name() << "\033[0m" << std::endl;
		}
		else
		{
			std::cout << i+1 << ". " << members[i]->get_name() << std::endl;
		}
	}


}

void Group::list_members(std::vector<bool> involved)
{
	for (int i = 0; i < (int)members.size(); i++)
	{
		if (involved[i]) std::cout << BLUE << i+1 << ". " << members[i]->get_name() << RESET << std::endl;
		else std::cout << i+1 << ". " << members[i]->get_name() << std::endl;
	}
}


std::string Group::get_name_of_member(int i)
{
	return members[i]->get_name();
}

void Group::sava_data_user(std::string name)
{
	std::ofstream file;
	file.open(filename_users_db, std::ios::app);
	file << name << std::endl;
	file.close();
}

void Group::save_data_expense(std::string name, float ammount, int who_paid_id, std::vector<bool> involved)
{
	// saving data about new expense to csv file
	std::ofstream file;
	file.open(filename_expenses_db, std::ios::app);
	file << name << "," << ammount << "," << who_paid_id << ",";
	for (int i = 0; i < (int)members.size(); i++)
	{
		if (involved[i]) file << "1,";
		else file << "0,";
	}
	file << std::endl;
	file.close();
}

void Group::print_expenses()
{
	// loading expenses
	std::ifstream expenses_file;
	std::string word, line;
	std::vector<std::string> words;
	expenses_file.open(filename_expenses_db);
	std::cout << std::setw(20) << std::left << "NAME" << std::setw(10) << std::right << "AMMOUNT" << std::setw(10) << "WHO PAID" << std::endl;
	if (expenses_file.good())
	{
		while (getline(expenses_file, line))
		{
			std::stringstream s(line);
			while (getline(s, word, ','))
			{
				words.push_back(word);
			}

			std::cout << std::setw(20) << std::left  << words[0] << std::setw(10) << std::fixed << std::setprecision(2) <<std::right << stof(words[1]);
			std::cout << std::setw(10) << this->members[stoi(words[2])]->get_name();
			std::cout << std::endl;
			words.clear();
		}
	}
	
}



std::ostream& operator<<(std::ostream& out, const Group& group)
{
	for (int i = 0; i < 45; i++) out << "-";
	out << std::endl;
	out << std::setw(10) << std::right << "NAME" << std::setw(10) << "SPENT" << std::setw(10)<< "DUE" << std::setw(10) << "BALANCE" << std::endl; 
	for (int i = 0; i < 45; i++) out << "-";
	out << std::endl;
	for (auto it = group.members.begin(); it < group.members.end(); it++)
	{
		out << (**it) << std::endl;
	}
	for (int i = 0; i < 45; i++) out << "-";
	out << std::endl;
	return out;
}
