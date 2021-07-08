#include <iostream> //Library for general I/O
#include <vector> //Improved data structures
#include <string> //Handles textual elements of address book
#include <algorithm> //Organisation
#include <fstream>
#include <sstream>
using namespace std;

class individual { //Class is preferred over struct, as data should be default private
private:
    string first_name = "";
    string second_name = "";
    string email = "";
    string phonenumber = ""; //Default this to string, as int would remove the '0' at the front.
    string address = "";
public:
    individual() {first_name = ""; second_name = ""; email = ""; phonenumber = ""; address = "";}
    individual (const string& firstname, const string& secondname, const string& emailaddress, const string& number, const string& personaddress) {
        first_name = firstname;
        second_name = secondname;
        email = emailaddress;
        phonenumber = number;
        address = personaddress; //Method to construct an entry for a person.
    }
    void setFirstName (const string& x) {first_name = x;}
    void setSecondName (const string& x) {second_name = x;}
    void setEmail (const string& x) {email = x;}
    void setPhoneNumber (const string& x) {phonenumber = x;}
    void setAddress (const string& x) {address = x;}
    //Wrote methods to use if wanting to adjust individual parameters, such as if a person changes phone or address
    string getFirstName() const {return first_name;}
    string getSecondName() const {return second_name;}
    string getEmail() const {return email;}
    string getPhoneNumber() const {return phonenumber;}
    string getAddress() const {return address;}
    //Functions to get individual parameters, having it in this format improves security, and ensures accidental tampering with person parameters does not occur during program use.
    
    //Elected to use const string references, the const is to ensure that data is maintained during the usage of functions, and is not manipulated in any way. T
    //The references allow the program to call in an address, and use the original version of the data as opposed to 'copying' the data to be used by the function, saving time and memory.
    friend istream &operator>>(istream &input, individual &X) {
        input >> X.first_name >> X.second_name >>  X.email >>  X.phonenumber >>  X.address;
        return input;
    }
    friend ostream &operator<<(ostream &output, const individual &X) {
        output << X.first_name << "," << X.second_name << "," <<  X.email << "," << X.phonenumber << "," << X.address;
        return output;
    }


};
vector<individual> Address_Book; //Vector is the most straight forward way to tackle this, building separate methods, although with more complexity, one could use a HashMap, allowing you to use parameters as Hash's, rather than writing explicit methods.
//Made this into a larger scope in order to support greater range of operations


void AddIndividual() {
    string firstname, lastname, email, phonenumber, address;
    cout << "Enter First Name: " << endl;
    cin.ignore();
    getline(cin, firstname);
    cout << "Enter Second Name: " << endl;
    getline(cin, lastname);
    cout << "Enter Email: " << endl;
    getline(cin, email);
    cout << "Enter Phone Number: " << endl;
    getline(cin, phonenumber);
    cout << "Enter Address: " << endl;
    getline(cin, address);
    individual X(firstname, lastname, email, phonenumber, address); //The function uses the developed constructor to pass in the parameters to generate the profile of a person, and pushed back.
    Address_Book.push_back(X);
}

void DisplayAddressBook() { //Displays parsed address file in a way that delimits and shows the parameters in a more user friendly way.
    for(int i = 0; i<Address_Book.size(); i++) {
        cout << "Index: " << i + 1 << ": " << "First Name: " << Address_Book[i].getFirstName() << ", Second Name: " << Address_Book[i].getSecondName() << ", Email: " << Address_Book[i].getEmail() << ", Phone Number: " << Address_Book[i].getPhoneNumber() << ", Address: " << Address_Book[i].getAddress() << endl;
    }
}

void DeleteIndividual() { 
    cout << "From the list of Addresses viewed here, please type the index of the individual you would like to delete" << endl;
    int userinput;
    cin >> userinput;
    if(cin.fail()) { //If an invalid number is typed
        cout << "Error! That was not a valid input, please type an index shown on screen, as a number to be deleted." << endl;
    }
    else {
        Address_Book.erase(Address_Book.begin() + userinput - 1); //Offsets and then erases the element selected by the user, shifted by 1 in order to start from 1 as the display shows.
        cout << "Deleted entry number: " << userinput << "!" << endl;
    }
}

void InitAddressBook() { //On startup, the file should be parsed to update the overall Address Book vector we use on startup, and then update the Address Book vector which will be manipulated by the user
    ifstream startup("Address_Book.txt");
    string line;
    while(getline(startup, line)) {
    vector<string> parsedparamaters;
    stringstream sstream(line); //create string stream from the string
     while(sstream.good()) {
        string substr;
        getline(sstream, substr, ','); //get first string delimited by comma
        parsedparamaters.push_back(substr); //Tokenizes the comma delimited string containing parameters
     }
    individual X(parsedparamaters[0], parsedparamaters[1], parsedparamaters[2], parsedparamaters[3], parsedparamaters[4]); //Passes in tokens into constructor, and adds to the vector.
    Address_Book.push_back(X);
    }
}

void searchBy() { //This function effectively waits for user input, then searches the vector by using the get functions made for the class, if the parameters match, a count will increment, displaying the index of the person, or indices if multiple users found
    int resultcount;
    string userchoice;
    string parameter = "";
    cout << "Select a parameter to search by: 'First Name', 'Last Name', 'Email', 'Telephone Number'" << endl;
    cin.ignore();
    getline(cin, userchoice);
    if(userchoice == "First Name") {
        cout << "Please type in the first name of the individual you would like to search for:" << endl;
        cin.ignore();
        getline(cin,parameter);
        int count = 0;
        vector<int>peoplefound;
        for(int i = 0; i < Address_Book.size(); i++) {
            if((Address_Book[i].getFirstName().find(parameter) != string::npos)) { //If string is found
                peoplefound.push_back(i+1); //Add to list of people found
                count = count + 1;
            }
        }
        if(count >= 2) { //If we find multiple people
            cout << "Multiple people found matching that first name:" << endl; 
            for(int i = 0; i<peoplefound.size();i++) {
                cout << "Matching user found at index: " << peoplefound[i] << endl;
            }
        }
        if(count == 1) {
            cout << "1 user found matching that first name. Found at index: " << peoplefound[0] << endl;
        }
        if(count = 0) { //If no user found
            cout << "No matching users found!" << endl;
        }
    }
    if(userchoice == "Last Name") {
        cout << "Please type in the last name of the individual you would like to search for:" << endl;
        cin.ignore();
        getline(cin,parameter);
        int count = 0;
        vector<int>peoplefound;
        for(int i = 0; i < Address_Book.size(); i++) {
            if(Address_Book[i].getSecondName().find(parameter) != string::npos) {
                peoplefound.push_back(i+1);
                count = count + 1;
            }
        }
        if(count >= 2) {
            cout << "Multiple people found matching that last name:" << endl;
            for(int i = 0; i<peoplefound.size();i++) {
                cout << "Matching user found at index: " << peoplefound[i] << endl;
            }
        }
        if(count == 1) {
            cout << "1 user found matching that last name. Found at index: " << peoplefound[0] << endl;
        }
        if(count = 0) {
            cout << "No matching users found!" << endl;
        }
    }
    if(userchoice == "Email") {
        cout << "Please type in the email of the individual you would like to search for:" << endl;
        cin.ignore();
        getline(cin,parameter);
        int count = 0;
        vector<int>peoplefound;
        for(int i = 0; i < Address_Book.size(); i++) {
            if((Address_Book[i].getEmail().find(parameter) != string::npos)) {
                peoplefound.push_back(i+1);
                count = count + 1;
            }
        }
        if(count >= 2) {
            cout << "Multiple people found matching that email:" << endl;
            for(int i = 0; i<peoplefound.size();i++) {
                cout << "Matching user found at index: " << peoplefound[i] << endl;
            }
        }
        if(count == 1) {
            cout << "1 user found matching that email. Found at index: " << peoplefound[0] << endl;
        }
        if(count = 0) {
            cout << "No matching users found!" << endl;
        }
    }
    if(userchoice == "Telephone Number") {
        cout << "Please type in the telephone number of the individual you would like to search for:" << endl;
        cin.ignore();
        getline(cin,parameter);
        int count = 0;
        vector<int>peoplefound;
        for(int i = 0; i < Address_Book.size(); i++) {
            if(Address_Book[i].getPhoneNumber().find(parameter) != string::npos) {
                peoplefound.push_back(i+1);
                count = count + 1;
            }
        }
        cout << count << endl;
        if(count >= 2) {
            cout << "Multiple people found matching that telephone number:" << endl;
            for(int i = 0; i<peoplefound.size();i++) {
                cout << "Matching user found at index: " << peoplefound[i] << endl;
            }
        }
        if(count == 1) {
            cout << "1 user found matching that telephone number. Found at index: " << peoplefound[0] << endl;
        }
        if(count = 0) {
            cout << "No matching users found!" << endl;
        }
    }
}

int main() {

    string input;
    InitAddressBook(); //First thing needed is to parse the current state of the address file to make sure the address book vector the user manipulates is up to date at start up
    while(1) {
        DisplayAddressBook();
        cout << "Please choose from the following commands: ADD - Adds a Person, DELETE - Removes a person, SEARCH - Finds a person based on parameter, EXIT - Exit program" << endl;
        cin >> input;
        if(input == "ADD") {
            AddIndividual();
        }
        if(input == "DELETE") {
            DeleteIndividual();
        }
        if(input == "SEARCH") {
            searchBy();
        }
        if(input == "EXIT") {
           break;
        }
    }
    ofstream addressfile;
    addressfile.open("Address_Book.txt"); //When the user types exit, we break from the continuous loop, and the current state of the manipulated address book vector is saved, and then written to the file, to be parsed again at next start up.
    for (const auto &e : Address_Book) addressfile << e << "\n"; //At the end of operation, the program writes the current contents of the Address Book to the file, which is updated.
}