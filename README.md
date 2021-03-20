# AirlineReservationSystem-Cpp

## 1. Project description
  The aim of this project was to familiarize with object oriented programming and to create more complex programs. The program contains many features such as logging in, booking a flight ticket, adding new flights, deleting accounts and many more. SQLite3 database was used in order to save all the changes made while the program was running.

## 2. User manual

  The program does not require performing any additional actions than running it. After compilation the login menu will pop up. By simply pressing the number and confirming it by pressing **Enter** we can go to the chosen option.


  Fig. 1 Login menu


  We can choose to login as a user, admin or create a new user account. User and admin menu requires providing email and password. During registration we have to provide name, surname, email and password.
  
  
  Fig. 2 Logging in
  
  After logging in we can again choose where the program should take us. All of the options are displayed and any of them can be chosen. 
  
## 3. Compilation
  Program was written with the use of CodeBlocks IDE alongside with C++ standard compiler. However if the user wants to modify its structure they have to install SQLite3 and add it to their compilers.

## 4. Source files
  Program was divided into cpp and header files so as it will be more pleasant to read:
* main.cpp - creating object User_Interface
* airline.cpp, airline.h - class Airline alongside with methods which allows us to read and write database which was created earlier
* user_interface.cpp, user_interface.h - class User_Interface alongside with methods which were used to create user friendly interface
* sqlite3.h - it was added alongside with library sqlite3.a to this project

## 5. Dependencies
  The following external libraries are used in the project:
* SQLite – database SQL engine. Website: https://sqlite.org/

## 6. Class description
  In the project the following classes were created:
- Airline
  * Airline() - constructor which establishes the connection with database,
  * void show_flights() - display all flights
  * void get_seats(string flight_id) - save positions of taken seats to the .txt file
  * void show_seats(string flight_id) - display plane seats
  * void show_customer_tickets() - show all tickets for specific customer
  * void show_all_tickets() - show all tickets
  * void add_reservation(string flight_id, int row, int col) - adding reservation for specific customer
  * bool check_availbility(string flight_id, int row, int col) - return true if seat is empty
  * void add_flight(string departure_airport, string destination_airport, string departure_datetime, string destination_datetime, string row, string col, double base_price) - add a flight
  * void cancel_reservation(string ticket_id) - cancel the reservation
  * bool user_login(string email, string password) - true if logged in
  * bool admin_login(string email, string password) - true if logged in
  * bool exists_flight(string flight_id) - true if flight with specific id exists
  * string getCurrent_log() - returns currently logged user/admin
  * void add_account(string name, string surname, string email, string password) - create a new account
  * void delete_account() - delete account of currently logged person

- User_Interface
  * User_Interface() - constructor which uses methods declared below
  * String input_string_check(string input) - string value check
  * Int input_int_check(int input) - int value check
  * Double input_doubl_check(double input) - double value check
  * void add_account() - create a new account
  * void delete_account() - delete the account
  * void login_menu() - login menu
  * void user_main_menu() - menu after user logged in
  * void admin_main_menu() - menu after admin logged in
  * void flights_menu() - display flights with options
  * void user_tickets_menu() - display user tickets with options
  * void admin_tickets_menu() - display all tickets with options
  * void cancel_reservation() - cancel reservation of currently logged user
  * void create_reservation(string flight_id) - create reservation for specific flight
  * void create_flight() - create a new flight with specific values
  * void user_chosen_flight() - display seats for chosen flight alongside with options
  * void admin_chosen_flight() - display seats for chosen flight alongside with options
  * Bool getUser() - return true if user logged in
  * void setUser(bool user) - change if user logs in/off
  * Bool getAdmin() - return true if admin logged in
  * void setAdmin(bool admin) - change if admin logs in/off
  * Bool getWorking() - value on which while loop operates until the program is terminated
  * void setWorking(bool working) - value set to false if user terminates program
  * Int getChoice() - reading the user choice for the options
  * void setChoice(int choice) - setting the user choice

##7. Resources
In the project the following resources are used:
- seat_callback.txt - file in which saved are the seats which are already taken
  - first column - rows, second column - columns, they are read in pairs inside of the program
- database.db - database which is used for this project
  - AIRPORT
  - CONTROLLER
  - FLIGHT
  - PASSENGER
  - TICKET

##8. Future development

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The first thing could be the improvement displaying the flights to filter it by departure/destination place or date. Another thing could be the deletion of chosen flight by admin, however it will require some kind of notification for passengers who have already bought the ticket for this flight.
