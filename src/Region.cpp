#include "Region.hpp"

using namespace std;

Region::Region(string _name, double _latitude, double _longitude, int _traffic)
{
    name = _name;
    latitude = _latitude;
    longitude = _longitude;
    traffic = _traffic;
}

string Region::get_name() { return name; }

double Region::get_latitude() { return latitude; }

double Region::get_longitude() { return longitude; }

int Region::get_traffic() { return traffic; }
