#ifndef __UTAXI_HPP__
#define __UTAXI_HPP__

#include "Region.hpp"
#include "User.hpp"
#include "Driver.hpp"
#include "Passenger.hpp"
#include "Trip.hpp"
#include "consts.hpp"
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

class Utaxi
{
public:
    void read_info(char *input_name);
    void start();

private:
    std::vector<std::string> seperate_line(std::string line);
    void add_region(std::vector<std::string> info);
    void post_commands(std::string command);
    void get_commands(std::string command);
    void delete_commands(std::string command);
    bool has_word(std::string line, std::string word);
    std::string find_next_word(std::string line, std::string word);
    void signup(std::string command);
    void post_trips(std::string commmand);
    void get_trips(std::string command);
    Trip *find_trip(std::string id);
    void delete_trips(std::string command);
    User *find_user(std::string username);
    void accept(std::string command);
    void finish(std::string command);
    std::vector<Trip> remove_cancelled_trips(std::vector<Trip> trip_list);
    bool username_exists(std::string username);
    bool user_has_trip(std::string username);
    bool read_bool(std::string word);
    Region *find_region(std::string region_name);
    void cost(std::string command);
    std::vector<Region> regions;
    std::vector<User *> users;
    std::vector<Trip> trips;
};

#endif
