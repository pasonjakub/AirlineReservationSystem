#include "airline.h"

int Airline::flight_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    cout<<"Flight number: \t\t\t"<<argv[0]<<endl;
    cout<<"\nFrom: \t\t\t\t"<<argv[1]<<endl;
    cout<<"To: \t\t\t\t"<<argv[2]<<endl;
    cout<<"Departure: \t\t\t"<<argv[3]<<endl;
    cout<<"Estimated time of arrival: \t"<<argv[4]<<endl;
    cout<<"\nPrice: \t\t\t\t"<<argv[5]<<"$"<<endl;
    cout<<"\n==========================================================\n"<<endl;
    return 0;
}

int Airline::ticket_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    cout<<"Ticket number: \t"<<argv[4]<<endl;
    cout<<"Passenger: \t"<<argv[8]<<" "<<argv[9]<<endl;

    cout<<"\nFrom: \t\t"<<argv[0]<<"\tDeparture: \t"<<argv[2]<<endl;
    cout<<"To: \t\t"<<argv[1]<< "\tArriving at: \t"<<argv[3]<<endl;
    cout<<"\nRow number: \t"<<argv[5]<<endl;
    cout<<"Column number: \t"<<argv[6]<<"\nPrice: \t\t"<<argv[7]<<"$"<<endl;
    cout<<"\n==========================================================\n"<<endl;
    return 0;
}

int Airline::seat_callback(void* NotUsed, int argc, char** argv, char** azColName)
{
    ofstream my_file("seat_callback.txt", ios::app);
    for(int i = 0; i < argc-1; i++){
        my_file << argv[i] <<" "<<argv[i+1] <<endl;
    }
    my_file.close();
    return 0;
}

int Airline::log_callback(void * NotUsed, int argc, char** argv, char** azColName)
{
    int check = stoi(argv[0]);

    if(check == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Airline::Airline() :dir("database.db")
{
    sqlite3_open(dir, &DB);
}

void Airline::show_flights()
{
    string sql = "SELECT ID_FLIGHT, DEPARTURE_AIRPORT_CODE, DESTINATION_AIRPORT_CODE, DEPARTURE_DATETIME, ARRIVAL_DATETIME, BASE_PRICE FROM FLIGHT;";
    sqlite3_exec(DB, sql.c_str(), flight_callback, NULL, NULL);
}

void Airline::get_seats(string flight_id)
{
    ofstream my_file;
    my_file.open("seat_callback.txt", ofstream::out | ofstream::trunc);
    my_file.close();
    string sql = "SELECT ROW_NUM, COL_NUM FROM TICKET WHERE ID_FLIGHT = " + flight_id + ";";
    sqlite3_exec(DB, sql.c_str(), seat_callback, NULL, NULL);
}

void Airline::show_seats(string flight_id)      //showing where is higher price, showing base price and premium price
{
    get_seats(flight_id);
    string sql = "SELECT ID_FLIGHT, DEPARTURE_AIRPORT_CODE, DESTINATION_AIRPORT_CODE, DEPARTURE_DATETIME, ARRIVAL_DATETIME, BASE_PRICE, PREMIUM_PRICE FROM FLIGHT WHERE ID_FLIGHT = " + flight_id + ";";
    sqlite3_exec(DB, sql.c_str(), flight_callback, NULL, NULL);

    int rows = 16;
    int cols = 7;

    for (int i=0; i<rows; i++) {
        for (int j = 0; j < cols; j++)
            m_seat_number[i][j] = " ";
    }
    ifstream my_file("seat_callback.txt");
    string a, b;
    while(my_file >> a >> b){
        m_seat_number[stoi(a)-1][stoi(b)-1] = 'X';
    }
    my_file.close();


    for(int i=0; i<cols-1; i++){
        if(i==cols/2) cout<<"               ";
        cout<<" "<<i+1;
    }

    cout<<"\n";
    for(int i=0; i<rows; i++) {
        for (int j = 0; j < cols ; j++) {
            if (j == cols / 2 ) {
                if (i < 9) {
                    if (i < rows*0.25)  cout << "| Premium 0" << i + 1 << " |";
                    else                cout << "| Economy 0" << i + 1 << " |";
                }
                else{
                    if (i < rows*0.25)  cout << "| Premium " << i + 1 << " |";
                    else                cout << "| Economy " << i + 1 << " |";
                }
            }
            cout << "-"<<m_seat_number[i][j];
            if(j == cols/2-1) cout<<"-";
        }
        cout << endl;
    }
}

void Airline::show_customer_tickets()
{
    string sql = "SELECT FLIGHT.DEPARTURE_AIRPORT_CODE, FLIGHT.DESTINATION_AIRPORT_CODE, FLIGHT.DEPARTURE_DATETIME, FLIGHT.ARRIVAL_DATETIME,"
    "TICKET.ID_TICKET, TICKET.ROW_NUM, TICKET.COL_NUM, TICKET.PRICE, PASSENGER.NAME_PASSENGER, PASSENGER.SURNAME_PASSENGER "
    "FROM TICKET "
    "INNER JOIN FLIGHT ON FLIGHT.ID_FLIGHT = TICKET.ID_FLIGHT "
    "INNER JOIN PASSENGER ON TICKET.EMAIL_PASSENGER = PASSENGER.EMAIL_PASSENGER WHERE TICKET.EMAIL_PASSENGER = '" + getCurrent_log() + "';";
    sqlite3_exec(DB, sql.c_str(), ticket_callback, NULL, NULL);
}

void Airline::show_all_tickets()
{
    string sql = "SELECT FLIGHT.DEPARTURE_AIRPORT_CODE, FLIGHT.DESTINATION_AIRPORT_CODE, FLIGHT.DEPARTURE_DATETIME, FLIGHT.ARRIVAL_DATETIME,"
    "TICKET.ID_TICKET, TICKET.ROW_NUM, TICKET.COL_NUM, TICKET.PRICE, PASSENGER.NAME_PASSENGER, PASSENGER.SURNAME_PASSENGER "
    "FROM TICKET "
    "INNER JOIN FLIGHT ON FLIGHT.ID_FLIGHT = TICKET.ID_FLIGHT "
    "INNER JOIN PASSENGER ON TICKET.EMAIL_PASSENGER = PASSENGER.EMAIL_PASSENGER";
    sqlite3_exec(DB, sql.c_str(), ticket_callback, NULL, NULL);
}

void Airline::add_reservation(string flight_id, int row, int col)
{
    char* messageError;

    string sql ="INSERT INTO TICKET (EMAIL_PASSENGER, ID_FLIGHT, ROW_NUM, COL_NUM, PRICE) "
    "VALUES('" + getCurrent_log() + "'," + flight_id + "," + to_string(row) + "," + to_string(col) + ", (SELECT CASE WHEN (SELECT ROW_NUMBER FROM FLIGHT "
    "WHERE ID_FLIGHT = " + flight_id + ") > " + to_string(4*row - 1) + " THEN PREMIUM_PRICE ELSE BASE_PRICE END CUSTOM_NAME FROM FLIGHT WHERE ID_FLIGHT = " + flight_id + "));";

    string sql_check = "SELECT CASE WHEN ROW_NUMBER > " + to_string(row - 1) + " THEN 1 ELSE 0 END AS CUSTOM_NAME FROM FLIGHT WHERE ID_FLIGHT = " + flight_id + ";";
    int xx = sqlite3_exec(DB, sql_check.c_str(), log_callback, NULL, NULL);
    if(xx == 4){
        int process = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(process != SQLITE_OK)
        {
            cerr << "\nIncorrect reservation insert!\n" << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "\nReservation made correctly!\n" << endl;
    }
    else
        cout<<"Incorrect input."<<endl;
}

void Airline::cancel_reservation(string ticket_id)
{
    char* messageError;
    string sql = "DELETE FROM TICKET WHERE ID_TICKET = " + ticket_id + " AND EMAIL_PASSENGER = '" + getCurrent_log() + "';";
    string sql_check = "SELECT CASE WHEN COUNT(ID_TICKET) > 0 THEN 1 ELSE 0 END AS CUSTOM_NAME FROM TICKET WHERE ID_TICKET = " + ticket_id + " AND EMAIL_PASSENGER = '" + getCurrent_log() + "';";
    int xx = sqlite3_exec(DB, sql_check.c_str(), log_callback, NULL, NULL);
    if(xx == 4){
        int process = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if(process != SQLITE_OK)
        {
            cerr << "\nError with canceling reservation!\n" << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "\nReservation canceled successfully!\n" << endl;
        }
    else{
        cout<<"Incorrect input."<<endl;
    }
}

bool Airline::check_availbility(string flight_id, int row, int col)   //true if empty
{
    ifstream my_file("seat_callback.txt");
    string a, b;
    while(my_file >> a >> b){
        if(to_string(row)!=a || to_string(col)!=b)
            continue;
        else{
            return !(to_string(row)==a && to_string(col)==b);
        }
    }
}

void Airline::add_flight(string departure_airport, string destination_airport, string departure_datetime, string destination_datetime, string row, string col, double base_price)
{
    char* messageError;
    string sql ="INSERT INTO FLIGHT (DEPARTURE_AIRPORT_CODE, DESTINATION_AIRPORT_CODE, DEPARTURE_DATETIME, ARRIVAL_DATETIME, ROW_NUMBER, COL_NUMBER, BASE_PRICE, PREMIUM_PRICE) "
                "VALUES('" + departure_airport + "','" + destination_airport + "','" + departure_datetime + "',"
                "'" + destination_datetime + "'," + row + "," + col + "," + to_string(base_price) + "," + to_string(base_price+15) + ");";

    int process = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if(process != SQLITE_OK)
    {
        cerr << "\nIncorrect flight insert!" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "\nFlight added correctly!" << endl;
}

bool Airline::user_login(string email, string password)
{
    string sql = "SELECT CASE WHEN COUNT(PASSWORD_PASSENGER) > 0 THEN 1 ELSE 0 END AS CUSTOMaNAME FROM PASSENGER "
    "WHERE EMAIL_PASSENGER = '" + email + "' AND PASSWORD_PASSENGER = '" + password +"';";
    int xx = sqlite3_exec(DB, sql.c_str(), log_callback, NULL, NULL);
    if(xx == 4){
        currently_logged = email;
        return true;
    }
    return false;
}

bool Airline::admin_login(string email, string password)
{
    string sql = "SELECT CASE WHEN COUNT(PASSWORD_CONTROLLER) > 0 THEN 1 ELSE 0 END AS CUSTOM_NAME FROM CONTROLLER "
    "WHERE EMAIL_CONTROLLER = '" + email + "' AND PASSWORD_CONTROLLER = '" + password + "';";
    int xx = sqlite3_exec(DB, sql.c_str(), log_callback, NULL, NULL);
    if(xx == 4){
        currently_logged = email;
        return true;
    }
    return false;
}

bool Airline::exists_flight(string flight_id)
{
    string sql = "SELECT CASE WHEN COUNT(ID_FLIGHT) > 0 THEN 1 ELSE 0 END AS CUSTOM_NAME FROM FLIGHT WHERE ID_FLIGHT = " + flight_id + ";";
    int xx = sqlite3_exec(DB, sql.c_str(), log_callback, NULL, NULL);
    if(xx == 4)
        return true;
    return false;
}

void Airline::add_account(string name, string surname, string email, string password)
{
    char* messageError;
    string sql = "INSERT INTO PASSENGER (NAME_PASSENGER, SURNAME_PASSENGER, EMAIL_PASSENGER, PASSWORD_PASSENGER) VALUES('" + name + "','" + surname + "','" + email + "','" + password + "')";
    int process = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if(process != SQLITE_OK)
    {
        cerr << "\nUnsuccessful account creation!" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "\nAccount created correctly!" << endl;
}

void Airline::delete_account()
{
    char* messageError;
    string sql = "DELETE FROM PASSENGER WHERE EMAIL_PASSENGER = '" + getCurrent_log() + "'; DELETE FROM TICKET WHERE EMAIL_PASSENGER = '" + getCurrent_log() + "' ;";
    int process = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if(process != SQLITE_OK)
    {
        cerr << "\nUnsuccessful account deletion!\n" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "\nAccount deleted correctly!\n" << endl;
}















