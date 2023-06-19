#ifndef __REGION_HPP__
#define __REGION_HPP__

#include <string>

class Region
{
public:
    Region(std::string _name, double _latitude, double _longitude, int _traffic);
    std::string get_name();
    double get_latitude();
    double get_longitude();
    int get_traffic();

private:
    std::string name;
    double latitude;
    double longitude;
    int traffic;
};

#endif
