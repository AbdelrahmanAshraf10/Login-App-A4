
// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login-App.cpp
// Last Modification Date: 5/17/2022
// Author1 and ID and Group: Abdelrahman Ashraf El-Sayed Abdalla    20210199    Group A
// Author2 and ID and Group: Aly Walaa El-Deen Yehia    20210250    Group A
// Author3 and ID and Group: Omar Amer Ahmed    20210267    Group A
// Teaching Assistant: Yousra
// Purpose: Creating a Login App

#include <iostream>
#include <regex>
#include <string>
#include <conio.h>
#include <vector>
#include <fstream>
using namespace std;


struct data    // Creating a struct to store users information
{
    string username;
    string email;
    string password;
    string pNumber;
};
vector<data> uservector;
data users;
//--------------------------------------------------------
void emailReg();
void Username();
void createPass();
void storeInfo();
void changepass();
void login();
//-------------------------------------------------------------------


int main()
{
    int choice;
    cout << "                                Welcome to Clowns Login App :) \n";
    cout << "\n";
    cout << "Please enter a choice from below: \n";
    cout << "1- Register\n";
    cout << "2- Login \n";
    cout << "3- Change password \n";
    cout << "4- Exit \n";

    cin >> choice;

    switch(choice)  // Making the user to choose an option to apply
    {
        case 1:
            emailReg();
            createPass();
            Username();
            storeInfo();
            cout << "Registration completed :)" << endl;
            break;
        case 2:
            login();
            break;
        case 3:
            changepass();
            break;
        case 4:
            cout << "Thanks for using Clowns Login App :)" << endl;
            return 0;
    }
}

void createPass()    // Creating a new password for the registration
{
    cout<<"Please be aware that there are certain characters allowed in the creation of a password.\n";
    cout<<"Password must contain of 8 characters or more and contains at least one of the following characters: \n";
    cout<<"[A-Z],[a-z],[0-9] & any special character like [!?#@$..etc]\n";
    string password  , cPassword , encPass = "";
    char c ,n;
    while(true)
    {
        cout<<endl<<"Please enter a new password: \n";
        while((c = getch()) != '\r' )
        {
            cout<<'*';
            password += c;
        }

        cout<<endl<<"Please confirm password: \n";
        while((n = getch()) != '\r'  )
        {
            cout<<'*';
            cPassword += n;
        }

        while(cPassword != password)
        {

            cout<<endl<<"Passwords doesn't match..Please try again: \n";
            cout<<"Please enter a new password: \n";
            password.clear();
            while((c = getch()) != '\r')
            {
                cout<<'*';
                password += c;
            }
            cPassword.clear();
            cout<<endl<<"Please confirm password again: \n";
            while((n = getch()) != '\r' )
            {
                cout<<'*';
                cPassword += n;
            }
        }

        regex pass ("(?=.*[a-z])(?=.*[0-9])(?=.*[A-Z])(?=.*[!@#$%^&*_+=-?.])[a-zA-Z0-9!@#$%^&*_+=-?.]{8,}");
        while (!regex_match(password,pass))
        {
            cout<<endl<<"Password is not strong enough.. Please enter a new one: \n";

            password.clear();
            while((c = getch()) != '\r'  )
            {
                cout<<'*';
                password += c;
            }
            cout<<endl<<"Please confirm password: \n";\

            password.clear();
            while((n = getch()) != '\r' )
            {
                cout<<'*';
                cPassword += n;
            }
        }
        if(cPassword == password)
        {
            cout<<endl;
            for(char i : password)
            {
                encPass += char(int(i)+1);

                users.password = encPass;
            }
            break;
        }
    }
}

void storeInfo()    // Storing the user's info. in the file
{
    fstream userFile;
    userFile.open("userdata.txt",ios::in | ios::out | ios::app);

    userFile<<users.email<<endl;
    userFile<<users.password<<endl;
    userFile<<users.username<<endl;
    userFile<<users.pNumber<<endl;
}

void emailReg()    // Creating a new email for the registration
{
    string email;
    cout<<"Please enter your email address: \n";
    cin>>email;
    regex pattern("[a-zA-Z0-9]+[@][a-z]+[.][a-z]+");
    while(!regex_match(email,pattern))
    {
        cout<<"Invalid email formula.. Please enter the email again: \n";
        cin.clear();
        cin>>email;
    }
    users.email = email;
}

void Username()    // Creating a new username and phone number for the registration
{
    string username;
    regex un ("([a-zA-Z]{3,}[_]*)");
    cout<<"Please enter your username \n";
    cin>>username;
    while(!regex_match(username,un))
    {
        cout<<"Invalid user name..Please try again: \n";
        cin.clear();
        cin>>username;

    }
    users.username = username;

    string pNumber;
    regex n ("([0][1]([0-9]+){9})");
    cout<<"Please enter your phone number: \n";
    cin>>pNumber;
    while(!regex_match(pNumber,n))
    {
        cout<<"Invalid number..Please try again: \n";
        cin.clear();
        cin>>pNumber;
    }
    users.pNumber = pNumber;

}

void changepass()   // Making the user to change their password
{
    string newpass, oldpass, confirmpass, encryptedpass;
    fstream userFile;
    userFile.open("userdata.txt", ios::in);

    while(!userFile.eof())
    {
        getline(userFile, users.email);
        getline(userFile, users.password);
        getline(userFile, users.username);
        getline(userFile, users.pNumber);

        uservector.push_back(users);
    }

    cout << "Please enter the old password: " << endl;
    while (true) {
        cin >> oldpass;
        for (char i: oldpass) {
            encryptedpass += char(int(i) + 1);
        }
        for (data users: uservector) {
            if (encryptedpass == users.password) {
                createPass();
                storeInfo();
                break;
            }
            else {
                cout << "Passwords dont match." << endl;
                break;
            }
        }
    }
}

void login()    // Making the user to log in the app
{
    string name, pass, line, encryptedpass = "";
    fstream userFile;
    userFile.open("userdata.txt",ios::in | ios::out | ios::app);

    while(!userFile.eof())
    {
        getline(userFile, users.email);
        getline(userFile, users.password);
        getline(userFile, users.username);
        getline(userFile, users.pNumber);

        uservector.push_back(users);
    }

    while(true)
    {
        cout << "Please enter your username: " << endl;
        cin >> name;
        for(data users: uservector) {
            while (name != users.username) {
                cout << "User name was not found Please try again: \n";
                cin >> name;
            }
            cout << "Please enter your password: \n";
            cin >> pass;
            for (char i: pass) {
                encryptedpass += char(int(i) + 1);
            }
            while (encryptedpass != users.password) {
                cout << "Password is not correct..Please try again: \n";
                cin >> pass;
                for (char i: pass) {
                    encryptedpass += char(int(i) + 1);
                }
            }
            cout << "Logged in successfully \n";
            break;
        }
    }
}
