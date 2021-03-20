#include <iostream>
#include "sqlite3.h"
#include <fstream>
#include "string"
#include <vector>

using namespace std;

class Airline
{
private:
    char* dir;
    string m_seat_number[16][7];
    sqlite3* DB;
    string currently_logged;
    static int flight_callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int ticket_callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int seat_callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int log_callback(void* NotUsed, int argc, char** argv, char** azColName);


public:
    Airline();  //constructor which establishes the connection with database
    void show_flights();    //display all flights
    void get_seats(string flight_id);       //save positions of seats to the .txt file
    void show_seats(string flight_id);      //display plane seats
    void show_customer_tickets();         //show all tickets for specific passenger
    void show_all_tickets();            //show all tickets
    void add_reservation(string flight_id, int row, int col);        //adding reservation for specific place
    bool check_availbility(string flight_id, int row, int col);       //return true if seat is empty
    void add_flight(string departure_airport, string destination_airport, string departure_datetime, string destination_datetime, string row, string col, double base_price);  //adding flight
    void cancel_reservation(string ticket_id);      //cancel the reservation
    bool user_login(string email, string password); //true if correctly logged in
    bool admin_login(string email, string password);    //true if correctly logged in
    bool exists_flight(string flight_id);   //true if flights with specific id exists
    string getCurrent_log() {return currently_logged;}; //returns currently logged user/admin
    void add_account(string name, string surname, string email, string password);   //create a new account
    void delete_account();  //delete account of currently logged person
};




