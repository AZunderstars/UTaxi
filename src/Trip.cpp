#include "Trip.hpp"

using namespace std;

Trip::Trip(Passenger *_passenger, Region *_origin, Region *_destination, int _id, bool in_hurry)
{
    passenger = _passenger;
    origin = _origin;
    destination = _destination;
    id = _id;
    status = WAITING;
    driver = new Driver(EMPTY_STRING);
    calculate_cost(in_hurry);
}

int Trip::get_id() const { return id; }

string Trip::get_status() { return status; }

void Trip::print()
{
    if (get_status() == CANCELED)
            throw runtime_error(NOT_FOUND);
    cout << id << OUTPUT_SEPERATOR << passenger->get_name() << OUTPUT_SEPERATOR << origin->get_name() << OUTPUT_SEPERATOR << destination->get_name()
         << OUTPUT_SEPERATOR << cost << OUTPUT_SEPERATOR << status << endl;
}

void Trip::cancel()
{
    status = CANCELED;
}

void Trip::accept(Driver *_driver)
{
    status = TRAVELING;
    driver = _driver;
}

void Trip::finish()
{
    status = FINISHED;
}

Passenger *Trip::get_passenger() { return passenger; }

Driver *Trip::get_driver() { return driver; }

double Trip::get_cost() { return cost; }

bool Trip::operator<(Trip const &trip)
{
    return cost > trip.cost;
}

void Trip::calculate_cost(bool in_hurry)
{
    double dist = DIST_CONST * sqrt(pow(origin->get_latitude() - destination->get_latitude(), 2) + pow(origin->get_longitude() - destination->get_longitude(), 2));
    cost = dist * (origin->get_traffic() + destination->get_traffic()) * PRIMARY_COST;
    if (in_hurry)
        cost *= HURRY_FACTOR;
}