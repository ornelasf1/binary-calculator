#include <iostream>
#include <cmath>
#include <string>
#include <new>
using namespace std;

void conv_to_bin(int base_ten_num);
void conv_to_int(string base_two_num);
void text_to_bin(string text);

void conv_to_bin(int base_ten_num){
	int original_ten = base_ten_num;	
	int * binary_num;					//Creates pointer for dynamic array binary_num
	binary_num = new int[base_ten_num];
	int count = 0;
	while (base_ten_num > 0){			//while loop creates binary number but in incorrect reverse order.
		int remainder = base_ten_num % 2;
		base_ten_num /= 2;
		binary_num[count] = remainder;
		count++;
	}
	string binary_text = "";
	for (int i = count; i >= 1; i--){			//for loop starts from 'count' and decreases, compares to 1 instead of 0 because array index
		binary_text += to_string(binary_num[i-1]);
	}
	int setOffour = binary_text.length()%4;		//Uses modulus to determine number of 0's it's off from being divisible by 4.
	while (setOffour != 0){
		binary_text.insert(0, 1, '0');		//Use .insert(int index, int iterations, char '0') to insert 0 into the string
		setOffour = binary_text.length() % 4;
	}
	for (int i = binary_text.length(); i > 0; i-=4){	//Splits the binary number string into groups of 4.
		binary_text.insert(i, 1, ' ');
	}
	cout << "Binary Representation of " << original_ten << " is " << binary_text << endl << endl;;
	delete[] binary_num;
	binary_num = NULL;
}

void conv_to_int(string base_two_num){
	string original_two = base_two_num;
	int power = 0;
	int binvalue = 0;
	for (int i = base_two_num.length(); i >= 1; i--){
		if (base_two_num[i-1] == '1'){
			char integer = base_two_num[i-1];
			//Assigning an int to a char will provide it's ASCI number.
			int value = integer-'/';			//ASCI number of integer after it was converted to int from char(49). 1(49)-/(47) = 2
			binvalue = binvalue + pow(value, power);
		}
		power++;
	}
	cout << "The value " << original_two << " represents " << binvalue << endl << endl;
}

void text_to_bin(string text_bin){
	int sizeofstr = text_bin.length();
	string bin_of_text;
	for (int i = 0; i < sizeofstr; i++){
		cout << (int)text_bin[i] << endl;
	}
}

int main(){
	reset:
	int choice;
	int base_ten;
	string base_two;
	string text;
	cout << "----------Binary Calculator----------" << endl
		<< "[1] Convert base 10 to base 2." << endl
		<< "[2] Convert base 2 to base 10." << endl
		<< "[3] Quit program." << endl;
	cin >> choice;
	switch (choice){
	case 1:
		cout << "What number do you want converted to binary?" << endl;
		cin >> base_ten;
		conv_to_bin(base_ten);
		goto reset;
	case 2:
		cout << "What binary set do you want converted to integer? (Only input 0's and 1's)" << endl;
		cin >> base_two;
		for (int i = 0; i < base_two.length(); i++){
			if ((base_two[i] == '0') || (base_two[i] == '1')){
				continue;
			}
			else{
				cout << "Only 1's and 0's are allowed as input!" << endl;
				goto reset;
			}
		}
		conv_to_int(base_two);
		goto reset;
	case 3:
		break;
	default:
		cout << "Invalid choice" << endl;
		goto reset;
	}
	system("pause");
}

