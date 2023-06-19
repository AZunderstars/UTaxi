#ifndef __TRIP_HPP__
#define __TRIP_HPP__

#include "Passenger.hpp"
#include "Driver.hpp"
#include "consts.hpp"
#include "Region.hpp"
#include "cmath"
#include <iostream>
#include <string>

class Trip
{
public:
    Trip(Passenger *_passenger, Region *_origin, Region *_destination, int _id, bool in_hurry);
    int get_id() const;
    std::string get_status();
    void print();
    void cancel();
    void accept(Driver *_driver);
    void finish();
    Passenger *get_passenger();
    Driver *get_driver();
    double get_cost();
    bool operator<(Trip const &trip);

private:
    void calculate_cost(bool in_hurry);
    Passenger *passenger;
    Driver *driver;
    Region *origin;
    Region *destination;
    int id;
    std::string status;
    double cost;
};

#endif
