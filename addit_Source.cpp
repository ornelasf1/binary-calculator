#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

void printMenu(int&);
bool GetInt(int&);
void conv_to_bin(int, int);
string conv_to_bin(int, string);
void conv_to_int(string);
void text_to_bin(string);

void printMenu(int& option){
	do{
		cout << "----------Binary Calculator----------" << endl
			<< "[1] Convert base 10 to base 2." << endl
			<< "[2] Convert base 2 to base 10." << endl
			<< "[3] Convert text to a binary file." << endl
			<< "[4] Translate a binary file to text." << endl
			<< "[5] Quit program." << endl;
	} while (!(GetInt(option)));
}

bool GetInt(int & n)
{
	string str;
	cout << "before asking" << endl;
	fflush(stdin);
	getline(cin, str);
	cout << "after asking" << endl;

	stringstream buffer(str);
	buffer >> n;

	if (!buffer)
	{
		cout << "Numerical values only!" << endl;
		cout << str << endl;
		return false;
	}
	if (!buffer.eof())
	{
		cout << "No value inputted!" << endl;
		return false;
	}
	return true;
}

void conv_to_bin(int base_ten_num, int opt = 1){
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
	cout << "Binary Representation of " << original_ten << " is " << binary_text << endl << endl;
	delete[] binary_num;
	binary_num = NULL;
}

string conv_to_bin(int base_ten_num, string opt){
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
		binary_text += to_string(binary_num[i - 1]);
	}
	int setOffour = binary_text.length() % 4;		//Uses modulus to determine number of 0's it's off from being divisible by 4.
	while (setOffour != 0){
		binary_text.insert(0, 1, '0');		//Use .insert(int index, int iterations, char '0') to insert 0 into the string
		setOffour = binary_text.length() % 4;
	}
	delete[] binary_num;
	binary_num = NULL;
	return binary_text;
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
	string bin_of_text = "";
	for (int i = 0; i < sizeofstr; i++){
		int temp = (int)text_bin[i];
		string binary_text = conv_to_bin(temp, "string");
		//cout << binary_text << ' ';
		bin_of_text.insert(bin_of_text.length(), binary_text+' ');
	}
	ofstream fstream;
	fstream.open("Binary_File.txt");
	fstream << bin_of_text;
	fstream.close();
	cout << "Binary string has been saved to \"Binary_File.txt\" in the project's folder." << endl;
}

void translate_file(){
	ifstream fobj;
	fobj.open("Binary_File.txt");
	if (!fobj.is_open()){
		cout << "\"Binary_File.txt\" was not found." << endl;
	}
	else{
		while (!fobj.eof()){
			char bit = fobj.get();
		}
	}

}

int main(){
	bool flag;
	int base_ten;
	int* choice = new int;
	string base_two;
	string text;
	do{
		printMenu(*choice);
		switch (*choice){
		case 1:
			cout << "What number do you want converted to binary?" << endl;
			cin >> base_ten;
			conv_to_bin(base_ten, 1);
			break;
		case 2:
			cout << "What binary set do you want converted to integer? (Only input 0's and 1's)" << endl;
			getline(cin, base_two);
			for (int i = 0; i < base_two.length(); i++){
				if ((base_two[i] == '0') || (base_two[i] == '1')){
					flag = true;
				}
				else{
					cout << "Only 1's and 0's are allowed as input!" << endl;
					flag = false;
					break;
				}
			}
			if (flag){
				conv_to_int(base_two);
			}
			break;
		case 3:
			cout << "Input text you want converted to binary." << endl;
			getline(cin, text);
			text_to_bin(text);
			break;
		case 4:
			translate_file();
			break;
		case 5:
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	} while (*choice != 5);
	delete choice;
	system("pause");
}

