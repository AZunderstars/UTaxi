#include "Utaxi.hpp"

using namespace std;

void Utaxi::read_info(char *input_name)
{
    string file_name = string(input_name);
    ifstream input_stream;
    input_stream.open(file_name);
    string line;
    getline(input_stream, line);
    while (input_stream)
    {
        getline(input_stream, line);
        vector<string> info = seperate_line(line);
        add_region(info);
    }
    input_stream.close();
}

vector<string> Utaxi::seperate_line(string line)
{
    vector<string> info;
    string word;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] != FILE_INPUT_SEPERATOR)
            word.push_back(line[i]);
        else
        {
            info.push_back(word);
            word.clear();
        }
    }
    info.push_back(word);
    return info;
}

void Utaxi::add_region(vector<string> info)
{
    string name = info[NAME_INDEX];
    double latitude = atof(info[LATITUDE_INDEX].c_str());
    double longitude = atof(info[LONGITUDE_INDEX].c_str());
    int traffic = stoi(info[TRAFFIC_INDEX]);
    regions.push_back(Region(name, latitude, longitude, traffic));
}

void Utaxi::start()
{
    cout << setprecision(2) << fixed;
    string command;
    while (getline(cin, command))
    {
        try
        {
            if (has_word(command, POST))
                post_commands(command);
            if (has_word(command, GET))
                get_commands(command);
            if (has_word(command, DELETE))
                delete_commands(command);
        }
        catch (runtime_error &e)
        {
            cout << e.what() << endl;
        }
    }
}

bool Utaxi::has_word(string line, string word)
{
    size_t found = line.find(word);
    return found != string::npos;
}

void Utaxi::post_commands(string command)
{
    string request = find_next_word(command, POST);
    if (request == SIGNUP)
        signup(command);
    else if (request == TRIPS)
        post_trips(command);
    else if (request == ACCEPT)
        accept(command);
    else if (request == FINISH)
        finish(command);
    else
        throw runtime_error(NOT_FOUND);
}

void Utaxi::finish(string command)
{
    string username = find_next_word(command, USERNAME);
    if (!username_exists(username))
        throw runtime_error(NOT_FOUND);
    string id = find_next_word(command, ID);
    if (stoi(id) > trips.size())
        throw runtime_error(NOT_FOUND);
    
    if (find_user(username)->get_user_type() != DRIVER_TYPE)
        throw runtime_error(PERMISSION_DENIED);
    Trip *finished_trip = find_trip(id);
    if (finished_trip->get_driver()->get_name() != username)
        throw runtime_error(BAD_REQUEST);
    finished_trip->finish();
    cout << OK;
}

void Utaxi::accept(string command)
{
    string username = find_next_word(command, USERNAME);
    if (!username_exists(username))
        throw runtime_error(NOT_FOUND);
    if (find_user(username)->get_user_type() != DRIVER_TYPE)
        throw runtime_error(PERMISSION_DENIED);
    Driver *driver = (Driver *)find_user(username);
    string id = find_next_word(command, ID);
    if (stoi(id) > trips.size())
        throw runtime_error(NOT_FOUND);
    Trip *accepted_trip = find_trip(id);
    if (accepted_trip->get_status() != WAITING || user_has_trip(username))
        throw runtime_error(BAD_REQUEST);
    accepted_trip->accept(driver);
    cout << OK;
}

bool Utaxi::user_has_trip(string username)
{
    for (int i = 0; i < trips.size(); i++)
    {
        if ((trips[i].get_passenger()->get_name() == username || trips[i].get_driver()->get_name() == username) && trips[i].get_status() != FINISHED)
            return true;
    }
    return false;
}

void Utaxi::post_trips(string command)
{
    string username = find_next_word(command, USERNAME);
    string origin_name = find_next_word(command, ORIGIN);
    string destination_name = find_next_word(command, DESTINATION);
    Region *origin = find_region(origin_name);
    Region *destination = find_region(destination_name);
    string in_hurry_string = find_next_word(command, IN_HURRY);
    bool in_hurry = read_bool(in_hurry_string);
    if (!username_exists(username))
        throw runtime_error(NOT_FOUND);
    if (find_user(username)->get_user_type() != PASSENGER_TYPE)
        throw runtime_error(PERMISSION_DENIED);
    Passenger *passenger = (Passenger *)find_user(username);
    if (user_has_trip(username))
        throw runtime_error(BAD_REQUEST);
    int id = trips.size() + TRIP_STARTING_INDEX;
    trips.push_back(Trip(passenger, origin, destination, id, in_hurry));
    cout << id << endl;
}

Region *Utaxi::find_region(string region_name)
{
    for (int i = 0; i < regions.size(); i++)
    {
        if (regions[i].get_name() == region_name)
            return &regions[i];
    }
    throw runtime_error(NOT_FOUND);
}

bool Utaxi::read_bool(string word)
{
    if (word == "yes")
        return true;
    else if (word == "no")
        return false;
    else
        throw runtime_error(BAD_REQUEST);
}
User *Utaxi::find_user(string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->get_name() == username)
            return users[i];
    }
    return NULL;
}

void Utaxi::signup(string command)
{
    string username = find_next_word(command, USERNAME);
    string role = find_next_word(command, ROLE);
    if (username_exists(username))
        throw runtime_error(BAD_REQUEST);
    if (role == DRIVER)
        users.push_back(new Driver(username));
    else if (role == PASSENGER)
        users.push_back(new Passenger(username));
    else
        throw runtime_error(BAD_REQUEST);
    cout << OK;
}

bool Utaxi::username_exists(string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]->get_name() == username)
            return true;
    }
    return false;
}

string Utaxi::find_next_word(string line, string word)
{
    size_t index = line.find(word);
    while (line[index] != TERMINAL_INPUT_SEPERATOR && line[index] != NULL_CHAR)
        index++;
    index++;
    string next_word;
    while (line[index] != TERMINAL_INPUT_SEPERATOR && line[index] != NULL_CHAR)
    {
        next_word.push_back(line[index]);
        index++;
    }
    return next_word;
}

void Utaxi::get_commands(string command)
{
    string request = find_next_word(command, GET);
    if (request == TRIPS)
        get_trips(command);
    else if (request == COST)
        cost(command);
    else
        throw runtime_error(NOT_FOUND);
}

void Utaxi::cost(string command)
{
    string username = find_next_word(command, USERNAME);
    string origin_name = find_next_word(command, ORIGIN);
    string destination_name = find_next_word(command, DESTINATION);
    Region *origin = find_region(origin_name);
    Region *destination = find_region(destination_name);
    string in_hurry_string = find_next_word(command, IN_HURRY);
    bool in_hurry = read_bool(in_hurry_string);
    if (!username_exists(username))
        throw runtime_error(NOT_FOUND);
    if (find_user(username)->get_user_type() != PASSENGER_TYPE)
        throw runtime_error(PERMISSION_DENIED);
    Passenger *passenger = (Passenger *)find_user(username);
    Trip trip(passenger, origin, destination, DEFAULT_ID, in_hurry);
    cout << trip.get_cost() << endl;
}

void Utaxi::get_trips(string command)
{
    string username = find_next_word(command, USERNAME);
    if (find_user(username)->get_user_type() != DRIVER_TYPE)
        throw runtime_error(PERMISSION_DENIED);
    if (has_word(command, ID))
    {
        Trip *printing_trip = find_trip(find_next_word(command, ID));
        if (printing_trip->get_status() == CANCELED)
            throw runtime_error(NOT_FOUND);
        printing_trip->print();
    }
    else
    {
        string sort_string = find_next_word(command, SORT_BY_STRING);
        bool to_sort = read_bool(sort_string);
        vector<Trip> trips_to_print = remove_cancelled_trips(trips);
        if (trips_to_print.empty())
            cout <<EMPTY;
        if (to_sort)
            sort(trips_to_print.begin(), trips_to_print.end());
        for (int i = 0; i < trips.size(); i++)
            trips_to_print[i].print();
    }
}

vector<Trip> Utaxi::remove_cancelled_trips(vector<Trip> trip_list)
{
    vector<Trip> updated_trips;
    for (int i = 0; i < trip_list.size(); i++)
    {
        if (trip_list[i].get_status() != CANCELED)
            updated_trips.push_back(trip_list[i]);
    }
    return updated_trips;
}

Trip *Utaxi::find_trip(string id)
{
    int id_int = stoi(id);
    int index;
    auto it = find_if(trips.begin(), trips.end(), [&id_int](Trip const &t)
                      { return t.get_id() == id_int; });
    if (it != trips.end())
        index = distance(trips.begin(), it);
    return &trips[index];
}

void Utaxi::delete_commands(string command)
{
    string request = find_next_word(command, DELETE);
    if (request == TRIPS)
        delete_trips(command);
    else
        throw runtime_error(NOT_FOUND);
}

void Utaxi::delete_trips(string command)
{
    string username = find_next_word(command, USERNAME);
    string id = find_next_word(command, ID);
    if (stoi(id) > trips.size())
        throw runtime_error(NOT_FOUND);
    Trip *deleted_trip = find_trip(id);
    if (find_user(username)->get_user_type() != PASSENGER_TYPE || deleted_trip->get_passenger()->get_name() != username)
        throw runtime_error(PERMISSION_DENIED);
    if (deleted_trip->get_status() != WAITING)
        throw runtime_error(BAD_REQUEST);
    deleted_trip->cancel();
    cout << OK;
}
