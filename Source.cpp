/*
	To test the login interfaces
	*/


	//Library
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;

/*
   Structurte for logged in page
   */
typedef struct
{
	string id;
	string pwd;
	string dep_code;
}LOGININFO;


//function Prototype

/*
  Interface design
  */
void login_page_design(void);
void signup_page_design(void);

/*
   User input
   */
string get_id();//Login
string get_pwd();//Login
string create_id();//Sign up
string create_pwd();//Sign up

/*
    Login phrase
*/
void select_page(void); //Main menu
void login_page(LOGININFO login_info); //Login
void signup_page(LOGININFO signup_info);//Sign up
void dep_select_page(void);
/*
    verify input format
	*/
void check_dep(const string &id); //Login and Sign up
bool is_valid_pwd(const string& pwd);//Login and Sign up
/*
  database
  */
bool login_dtbase_verif(const string& id, const string& pwd);//Login
bool NRIC_dtbase_verif(const string& ic);//Sign up
bool new_idpwd_dtbase_create(LOGININFO login_info,const string& ic);//Sign up




int main()
{
	select_page();

		return 0;
}

void login_page_design(void) {
	system("cls");
	cout << "\n**********************************************";
	cout << "\n*          WORK FROM HOME SYSTEM             *";
	cout << "\n*                LOGIN PAGE                  *";
	cout << "\n                  Welcome! ";
	cout << "\n**********************************************\n";
}

void signup_page_design(void) {
	system("cls");
	cout << "\n**********************************************";
	cout << "\n*          WORK FROM HOME SYSTEM             *";
	cout << "\n*                SIGN UP PAGE                *";
	cout << "\n                  Welcome! ";
	cout << "\n**********************************************\n";
}

string get_id() {
	string id;
	cout << "Please type your id(Example:UE23125678):" << endl;
	cin >> id;
	return id;
}

string get_pwd() {
	string pwd;
	cout << "Please type your password:" << endl;
	cin >> pwd;
	return pwd;
}


void select_page(void)
{
	char choice = '0';
	int select_count = 0;
	do {
		LOGININFO login_info, signup_info;
	
		login_page_design();
		cout << "| PRESS 1. LOGIN                             |" << endl;
		cout << "| PRESS 2. REGISTER                          |" << endl;
		cout << "| PRESS 3. QUIT                              |" << endl;
		if (select_count >= 1) {
			cout << "Invalid input!Please try again!";
		}

		cout << "\nPlease enter your choice : ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			login_page(login_info);
			break;

		case '2':
			signup_page(signup_info);
			break;

		case '3':
			return;
			break;

		default:
			select_count++;
		
				
		}
	} while (choice != '1' ||
		choice != '2' ||
		choice != '3');
	return;
}


	

void login_page(LOGININFO login_info)
{
	string id, pwd;
	string dep_code;
	bool valid = false;
	int login_count;
	login_count = 0;

	do {
		login_page_design();
		
		if (login_count >= 1)
		{
			cout << "Wrong ID or password,Please try again!" << endl;
		}

		get_id();
		dep_code = id.substr(0, 2);
		transform(dep_code.begin(), dep_code.end(),
			dep_code.begin(), ::tolower);
		check_dep(id);

		get_pwd();
		is_valid_pwd(pwd);
		login_dtbase_verif(id, pwd);
		login_count++;

	} while (!valid);
}
	

void signup_page(LOGININFO signup_info) {
	string id, pwd;
	string dep_code;
	int signup_count = 0;
	

	bool valid = false;

	do {
		signup_page_design();
		cout << "Please type your id provided by HR(Example:UE23BQ5678):";
		cin >> id;
		dep_code = id.substr(0, 2);
		transform(dep_code.begin(), dep_code.end(),
			dep_code.begin(), ::tolower);
		check_dep(id);
		cout << "Please create your new password(Must include one of @*#%!:";
		cin >> pwd;
		is_valid_pwd(pwd);
		NRIC_dtbase_verif(id);
	} while (!valid);

}







//Check department based on id
void check_dep(const string& id)
{

	if (!id.length() == 11) {
		cout << "invalid ID" << endl;
		return;

	}
	return;
}

	//Get the user password from input




	//Check the validity of the user password
	bool is_valid_pwd(const string & pwd)
		 {
	
	
			return pwd.find('@') != string::npos ||
			   pwd.find('*') != string::npos ||
			   pwd.find('#') != string::npos || 
			   pwd.find('%') != string::npos || 
			   pwd.find('!') != string::npos;
     }

		bool login_dtbase_verif(const string& id, const string& pwd)
		{
		
	        string idpwd = id+pwd;
		
			ifstream in_file("dtbase.txt");
			

			if (!in_file) {
				cout << "Error : Could not found the database file.";
				return false;
			}

			string line;
			while (getline(in_file,line)){
				if (line == idpwd) { //compare each line with the concatened idpwd

					return true; //Match found, return true
				}
			}

			//If not found,return false
			return false;
		}

		bool NRIC_dtbase_verif(const string& ic) {
			ifstream in_file("dtbase.txt");

			if (!in_file) {
				cout << "Error : Could not found the database file.";
				return false;
			}

			string line[12];
				while (getline(in_file, line[12])) {
					if (line[12] == ic) { //compare each line with the concatened idpwd
						cout << "Account already exist!Failed to create account";
						return false; //Match found, return false
					}
				}

				//If not found,return true
				return true;

				


		}

		bool new_idpwd_dtbase_create(LOGININFO login_info,const string& ic) {
			ifstream in_file("dtbase.txt", ios:: app);

			if (!in_file) {
				cout << "Error : Could not found the database file.";
				return false;
			}

			string id, pwd, dep_code;
			string line[12];

			while (getline(in_file, line[12])) {
				if (line[12] == ic) { //compare each line with the ic
					cout << "Account already exist!Failed to create account";
					return false; //Match found, return false
				}
			}

			//If not found,return true
		
			return true;


		}


	



