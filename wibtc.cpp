/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wibtc.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kngwato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:57:21 by kngwato           #+#    #+#             */
/*   Updated: 2017/05/09 22:58:21 by kngwato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

using namespace std;

//WIBTC class of people
class 	WIBTC
{
	public:

		WIBTC(string _idNumber, string _name, int _gender)
		{
			setDetails(_idNumber, _name, _gender);
		}

		WIBTC()
		{
			name		= "";
			idNumber	= "";
			gender		= -1;
		}

		void	setDetails(string _idNumber, string _name, int _gender)
		{
			name 		=	_name;
			idNumber	=	_idNumber;
			gender		= 	_gender;
		}

		string	getIDNumber(void)const
		{
			return	(idNumber);
		}

		string	etName(void)const
		{
			return	(name);
		}

		int	getGender(void)const
		{
			return	(gender);
		}

	private:

		string  name;
		string  idNumber;
		int     gender;
};

//Convert a char to integer
int 	char_to_int(char c)
{
	if (c >= '0' && c <= '9')
	{
		return ((int)c - 48);
	}
	return (0);
}

//Check if ID contains only digits
int 	isNumeric(string str)
{
	unsigned long i = 0;
	while (i < str.length())
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

//Check if ID number is valid
int		isValidID(string id)
{
	int month;
	int day;
	int citizenship;
	int total = 0;
	int checksum;
	int temp;
	//ID is valid if it has format YYMMDDSSSSCAZ
	//and has 13 digits
	if (id.length() == 13 && isNumeric(id))
	{
		month 	= 	char_to_int(id[2])*10 + char_to_int(id[3]);
		day 	= 	char_to_int(id[4])*10 + char_to_int(id[5]);
		if (day <= 31 && month <= 12)
		{
			citizenship =   char_to_int(id[10]);//citizenship is between 0 and 1
			if (citizenship >= 0 && citizenship <= 1)
			{
				checksum = char_to_int(id[12]);//last digit is a checksum
				for (int i = 0; i < 12; i++)
				{
					if (i % 2)
					{
						temp = char_to_int(id[i]) * 2;
						if (temp > 9)
							temp -= 9;
						total += temp;//sum of every other digit from the 1st digit on the left
					}
					else
					{
						total += char_to_int(id[i]);
					}
				}
				if (((total * 9) % 10) == checksum)
					return (1);
				else
					return (0);
			}
			else
			{
				return (0);
			}
		}
		else
		{
			return (0);
		}
	}
	else
	{
		return (0);
	}
}

//Checking if a person was born before the 16th of June
void	isBornBefore16June(WIBTC wibtc)
{
	int day;
	int month;

	if (isValidID(wibtc.getIDNumber()))
	{
		month 	= 	char_to_int(wibtc.getIDNumber()[2])*10 + char_to_int(wibtc.getIDNumber()[3]);
		day 	= 	char_to_int(wibtc.getIDNumber()[4])*10 + char_to_int(wibtc.getIDNumber()[5]);

		if (day < 16 && month < 6)
		{
			if (wibtc.getGender() >= 0)
			{
				if (wibtc.getGender() == 0)
				{
					cout << "Name: " << wibtc.getName() << "\nGender: Male\n";
				}
				else
				{
					cout << "Name: " << wibtc.getName() << "\nID: " << wibtc.getIDNumber() << "\n";
				}
			}
		}
		else
		{
			cout << "Not born before the 16th of June.\n";
		}
	}
	else
	{
		cout << "ID is invalid.\n";
	}
}

//Checking if a person was born after the 16th of March
int		isBornAfter16March(string id)
{
	int day;
	int month;

	if (isValidID(id))
	{
		month 	= 	char_to_int(id[2])*10 + char_to_int(id[3]);
		day 	= 	char_to_int(id[4])*10 + char_to_int(id[5]);
		if (day > 16 && month > 3)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	return (0);
}

//Count people born after 16th March and invalid IDs
void	checkPoeple(WIBTC *people, int numberOfPeople)
{
	int validIDs = 0;
	int bornAfter16March = 0;

	for (int i = 0; i < numberOfPeople; i++)
	{
		if (isValidID(people[i].getIDNumber()))
			validIDs++;
		if (isBornAfter16March(people[i].getIDNumber()))
			bornAfter16March++;
	}
	cout << "Valid IDs: " << validIDs << "\n";
	cout << "Born after March: " << bornAfter16March << "\n";
}

int main(void)
{
	WIBTC people[6];
	people[0].setDetails("8910150193085","Brute Force",1);
	people[1].setDetails("6206025432080","Enum Git",0);
	people[2].setDetails("8212300383083","Kole Typedef",1);
	people[3].setDetails("6312015439089","Tom Args",0);
	people[4].setDetails("6908025462081","Lonely Stream",0);
	people[5].setDetails("8501016184086","Smokey Port",0);

	//Born before 16th June check
	isBornBefore16June(people[2]);

	cout << "*************************************************\n\n";

	//Count people born after 16th March and invalid IDs
	checkPoeple(people,6);
	return (0);
}

