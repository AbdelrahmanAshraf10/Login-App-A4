#include <iostream>
#include <regex>
#include <string>
#include <conio.h>
#include <map>
#include <fstream>
using namespace std;


struct data
{
    string username;
    string email;
    string password;
    string pNumber;
};
map <string , data> usermap;
data users;
//--------------------------------------------------------
string emailReg();
string phoneNum();
string Username();
void displayMenu();
string createPass();
void storeInfo();

//-------------------------------------------------------------------


int main()
{

    emailReg();
    createPass();
    Username();
    phoneNum();
    storeInfo();

}


string createPass()
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



    return password;
}

void storeInfo()
{
    fstream userFile;
    userFile.open("userdata.txt",ios::in | ios::out | ios::app);

    userFile<<users.email<<endl;
    userFile<<users.password<<endl;
    userFile<<users.username<<endl;
    userFile<<users.pNumber<<endl;


}

string emailReg()
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
    return (email);
}

string phoneNum()
{
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
    cout<<"Registration complete \n";
    users.pNumber = pNumber;
    return(pNumber);
}

string Username()
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
}




