#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;


class User{
public:
    string username;
    string password;

    // Default constructor
    User() : username(""), password("") {}

    //constructor with parameters
    User(string username, string password):username(username), password(password){}

};


User UserEntry(){
    string username;
    string password;

    cout << "Enter your username: ";
    cin >> username;

    cout <<"enter password: ";
    cin >> password;

    return User(username, password);

}


class ManagerUser{

private:
    //map functions as memory container
    map <string, User> users;
    string username;
    string password;



    //method to save user credentials from the memory into the file
    void saveUser(){

        //create and open file to write. (trunc mode to clear existing data)
        ofstream UserFile("userfile.txt");

        if(UserFile.is_open()){
            UserFile << "username" << "   " << "password" << "\n";

            //iterate through the map
            for(const auto& pair: users){
                UserFile <<  pair.first <<"            " << pair.second.password <<"\n";
            }
            UserFile.close();
        }
        else{
            cout << "There is an error. Unable to open file";
        }
    }


    //method to load user credentials from file to memory when the program is executed
    void loadUser(){

        //open file while reading
        ifstream UserFile("userfile.txt");

        if (UserFile.is_open()){

                //read each line in the file and gets the corresponding usernames and passwords. End where the file ends
                while(UserFile >> username >> password){
                    // Create each new User with the username and password. Use username as key because of its uniqueness. noting that map is unique
                    users[username] = User(username, password);
                    }
                UserFile.close();
        }
        else{
            cout << "There is an error. the file was not properly opened.";
        }
    }


public:

    ManagerUser() {
        // Ensure the file is created at program start and load existing users if any
        //loadUser();
        ofstream UserFile("userfile.txt");
    }

    //method to register new users
    void registerUser(){
        //loadUser();

        //create object of User and give it value new user
        User newUser = UserEntry();

        if (users.find(newUser.username) != users.end()){
            cout << "Username already used. Try another one" << "\n";
        }
        else{
            users[newUser.username] = newUser;
            saveUser();
            cout << " User successfully registered" << "\n";
        }
    }



    void loginUser() {
       // loadUser();
        string username, password;

        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (users.find(username) != users.end() && users[username].password == password) {
            cout << "Login successful.\n";
        } else {
            cout << "Login failed. Incorrect username or password.\n";
        }
    }

};

int main() {

    ManagerUser userManager;


    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                userManager.registerUser();
                break;
            case 2:
                userManager.loginUser();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
