#include "gui.h"

string User_Interface::input_string_check(string input)
{
    while(!(cin >> input)){
        cin.clear();
        cin.ignore();
        cout << "Incorrect input."<<endl;
    }
    return input;
}

int User_Interface::input_int_check(int input)
{
    while(!(cin >> input)){
        cin.clear();
        cin.ignore();
        cout << "Incorrect input."<<endl;
    }
    return input;
}

double User_Interface::input_double_check(double input)
{
    while(!(cin >> input)){
        cin.clear();
        cin.ignore();
        cout << "Incorrect input."<<endl;
    }
    return input;
}

User_Interface::User_Interface() :m_working(true), m_admin(false), m_user(false)
{
    while(getWorking()){
        system("CLS");
        cout<<"================Airline Reservation System================\n"<<endl;
        cout<<"1. User"<<endl;
        cout<<"2. Admin"<<endl;
        cout<<"3. Add account"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"\nPlease choose an option: ";
        setChoice(input_int_check(getChoice()));
        switch(getChoice()){
        case 1:
            login_menu();
            user_main_menu();
            break;
        case 2:
            login_menu();
            admin_main_menu();
            break;
        case 3:
            add_account();
            break;
        case 4:
            setWorking(false);
            break;
        default:
            cout<<"Incorrect input."<<endl;
            system("pause");
        }
    }
}

void User_Interface::add_account()
{
    string name, surname, email, password;
    cout<<"Please provide your name: ";
    name = input_string_check(name);
    cout<<"Please provide your surname: ";
    surname = input_string_check(surname);
    cout<<"Please provide your email: ";
    email = input_string_check(email);
    cout<<"Please provide your password: ";
    password = input_string_check(password);
    a.add_account(name, surname, email, password);
    system("pause");
}

void User_Interface::delete_account()
{
    string password;
    system("cls");
    cout<<"================Airline Reservation System================\n"<<endl;
    cout<<"Do you want to delete your account?"<<endl;
    cout<<"1. Yes"<<endl;
    cout<<"2. No"<<endl;
    cout<<"\nPlease choose an option: ";
    switch(input_int_check(getChoice())){
    case 1:
        cout<<"Please type in your password to confirm: ";
        password = input_string_check(password);
        if(a.user_login(a.getCurrent_log(), password)){
            cout<<"The account is being deleted"<<endl;
            a.delete_account();
            setUser(false);
        }
        else{
            cout<<"Incorrect password"<<endl;
        }
        system("pause");
        break;
    case 2:
        break;
    default:
        cout<<"Incorrect input."<<endl;
        system("pause");
    }
}

void User_Interface::login_menu()
{
    string email, password;

    cout<<"Please provide your email: ";
    email = input_string_check(email);
    cout<<"Please provide your password: ";
    password = input_string_check(password);

    if(getChoice() == 1 && a.user_login(email,password)){
        cout<<"Correctly logged in!"<<endl;
        m_user = true;
    }
    else if(getChoice() == 2 && a.admin_login(email,password)){
        cout<<"Correctly logged in!"<<endl;
        m_admin = true;
    }
    else{
        cout<<"Incorrect login or password!"<<endl;
    }
    system("pause");
}

void User_Interface::user_main_menu()
{
    while(getUser()){
        system("CLS");
        cout<<"================Airline Reservation System================\n"<<endl;
        cout<<"1. Show flights"<<endl;
        cout<<"2. Show your tickets"<<endl;
        cout<<"3. Logout"<<endl;
        cout<<"4. Delete your account"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"\nPlease choose an option: ";
        switch(input_int_check(getChoice())){
        case 1:
            flights_menu();
            switch(input_int_check(getChoice())){      //flight_display_menu
            case 1:
                user_chosen_flight();
                break;
            case 2:
                break;
            case 3:
                setWorking(false);
                setUser(false);
                break;
            default:
                cout<<"Incorrect input."<<endl;
                system("pause");
            }
            break;
        case 2:
            user_tickets_menu();
            break;
        case 3:
            setUser(false);
            break;
        case 4:
            delete_account();
            break;
        case 5:
            setWorking(false);
            setUser(false);
            break;
        default:
            cout<<"Incorrect input. ";
            system("pause");
        }
    }
}

void User_Interface::admin_main_menu()
{
    while(getAdmin()){
        system("CLS");
        cout<<"================Airline Reservation System================\n"<<endl;
        cout<<"1. Show flights"<<endl;
        cout<<"2. Add flight"<<endl;
        cout<<"3. Show all tickets"<<endl;
        cout<<"4. Logout"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"\nPlease choose an option: ";
        switch(input_int_check(getChoice())){
        case 1:
            flights_menu();
            switch(input_int_check(getChoice())){
            case 1:
                admin_chosen_flight();
                break;
            case 2:
                break;
            case 3:
                setWorking(false);
                setAdmin(false);
                break;
            default:
                cout<<"Incorrect input. ";
                system("pause");
            }
            break;
        case 2:
            create_flight();
            system("pause");
            break;
        case 3:
            admin_tickets_menu();
            break;
        case 4:
            setAdmin(false);
            break;
        case 5:
            setWorking(false);
            setAdmin(false);
            break;
        default:
            cout<<"Incorrect input. ";
            system("pause");
        }
    }
}

void User_Interface::flights_menu()
{
    system("CLS");
    cout<<"================Airline Reservation System================\n"<<endl;
    a.show_flights();
    cout<<"1. Display available seats in a chosen flight"<<endl;
    cout<<"2. Return to main menu"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"\nPlease choose an option: ";
}

void User_Interface::user_tickets_menu()
{
    system("CLS");
    cout<<"================Airline Reservation System================\n"<<endl;
    a.show_customer_tickets();
    cout<<"1. Cancel reservation"<<endl;
    cout<<"2. Return to main menu"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"\nPlease choose an option: ";

    switch(input_int_check(getChoice())){      //user_tickets_menu
    case 1:
        cancel_reservation();
        break;
    case 2:
        break;
    case 3:
        setWorking(false);
        setUser(false);
        break;
    default:
        cout<<"Incorrect input. ";
        system("pause");
    }
}

void User_Interface::user_chosen_flight()
{
    cout<<"Please type in flight id: ";
    string flight_id;
    flight_id = input_string_check(flight_id);
    if(a.exists_flight(flight_id)){
        system("CLS");
        cout<<"================Airline Reservation System================\n"<<endl;
        a.get_seats(flight_id);
        a.show_seats(flight_id);
        cout<<"\n1. Book a ticket"<<endl;
        cout<<"2. Return to main menu"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"\nPlease choose an option: ";
        switch(input_int_check(getChoice())){          //seat_display_menu
        case 1:
            create_reservation(flight_id);
            break;
        case 2:
            break;
        case 3:
            setWorking(false);
            setUser(false);
            break;
        default:
            cout<<"Incorrect input."<<endl;
            system("pause");
        }
    }
    else{
        cout<<"Incorrect flight number."<<endl;
        system("pause");
    }
}

void User_Interface::admin_chosen_flight()
{
    cout<<"Please type in flight id: ";
    string flight_id;
    flight_id = input_string_check(flight_id);
    if(a.exists_flight(flight_id)){
        system("CLS");
        cout<<"================Airline Reservation System================\n"<<endl;
        a.get_seats(flight_id);
        a.show_seats(flight_id);
        cout<<"1. Return to main menu"<<endl;
        cout<<"2. Exit"<<endl;
        cout<<"\nPlease choose an option: ";
        switch(input_int_check(getChoice())){          //seat_display_menu
        case 1:
            break;
        case 2:
            setWorking(false);
            setAdmin(false);
            break;
        default:
            cout<<"Incorrect input. ";
            system("pause");
        }
    }
    else{
        cout<<"Incorrect flight number."<<endl;
        system("pause");
    }
}

void User_Interface::admin_tickets_menu()
{
    system("CLS");
    cout<<"================Airline Reservation System================\n"<<endl;
    a.show_all_tickets();
    cout<<"1. Return to main menu"<<endl;
    cout<<"2. Exit"<<endl;
    cout<<"\nPlease choose an option: ";
    switch(input_int_check(getChoice())){
    case 1:
        break;
    case 2:
        setWorking(false);
        setAdmin(false);
        break;
    default:
        cout<<"Incorrect input. ";
        system("pause");
    }
}

void User_Interface::cancel_reservation()
{
    string ticket_id;
    cout<<"Please type in ticket id which you want to cancel: ";
    ticket_id = input_string_check(ticket_id);

    a.cancel_reservation(ticket_id);

    system("pause");
}

void User_Interface::create_reservation(string flight_id)
{
    int row, col;
    cout<<"Please choose the row: ";
    row = input_int_check(row);
    cout<<"Please choose the column: ";
    col = input_int_check(col);

    if(a.exists_flight(flight_id)){
        if(a.check_availbility(flight_id, row, col)){
            a.add_reservation(flight_id, row, col);
            system("pause");
        }
        else{
            cout<<"This place is already taken!"<<endl;
            system("pause");
        }
    }
    else{
        cout<<"This flight does not exist"<<endl;
        system("pause");
    }

}


void User_Interface::create_flight()
{
    string departure_airport, destination_airport, departure_date, departure_time, destination_date, departure_datetime, destination_time, destination_datetime;
    double base_price;
    cout<<"Please type in departure airport code: ";
    departure_airport = input_string_check(departure_airport);
    cout<<"Please type in destination airport code: ";
    destination_airport = input_string_check(destination_airport);
    cout<<"Please type in departure date (DD.MM.YYYY): ";
    departure_date = input_string_check(departure_date);
    cout<<"Please type in departure time (HH:MM): ";
    departure_time = input_string_check(departure_time);
    departure_datetime = departure_date + " " + departure_time;
    cout<<"Please type in destination date (DD.MM.YYYY): ";
    destination_date = input_string_check(destination_date);
    cout<<"Please type in destination time (HH:MM): ";
    destination_time = input_string_check(destination_time);
    destination_datetime = destination_date + " " + destination_time;
    cout<<"Please type in base price for a ticket: ";
    base_price = input_double_check(base_price);
    a.add_flight(departure_airport, destination_airport, departure_datetime, destination_datetime, "16", "6", base_price);
}


















