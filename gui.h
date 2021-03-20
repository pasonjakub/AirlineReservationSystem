#include <iostream>
#include <string>
#include "sqlite3.h"
#include "airline.h"

using namespace std;

class User_Interface
{
private:
    Airline a;
    bool m_user, m_admin, m_working;
    int m_choice;
    string m_flight_id;
public:
    User_Interface();       //constructor which uses methods declared below
    string input_string_check(string input);        //string value check
    int input_int_check(int input);     //int value check
    double input_double_check(double input);        //double value check

    void add_account();     //create a new account
    void delete_account();      //delete the account
    void login_menu();      //login menu
    void user_main_menu();      //menu after user logged in
    void admin_main_menu();     //menu after admin logged in
    void flights_menu();        //display flights with options
    void user_tickets_menu();       //display user tickets with options
    void admin_tickets_menu();      //display all tickets with options
    void cancel_reservation();      //cancel reservation of currently logged user
    void create_reservation(string flight_id);      //create reservation for specific flight
    void create_flight();       //create a new flight with specific values
    void user_chosen_flight();      //display seats for chosen flight alongside with options
    void admin_chosen_flight();     //display seats for chosen flight alongside with options

    bool getUser() {return m_user;};        //return true if user logged in
    void setUser(bool user) {m_user = user;};       //change if user logs in/off

    bool getAdmin() {return m_admin;};      //return true if admin logged in
    void setAdmin(bool admin) {m_admin = admin;};   //change if admin logs in/off

    bool getWorking() {return m_working;};  //value on which while loop operates until the program is terminated
    void setWorking(bool working) {m_working = working;};       //value set to false if user terminates program

    int getChoice() {return m_choice;};     //reading the user choice for the options
    void setChoice(int choice) {m_choice = choice;};    //setting the user choice




};
