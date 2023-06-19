#ifndef __PASSENGER_HPP__
#define __PASSENGER_HPP__

#include "User.hpp"
#include "consts.hpp"
#include <string>

class Passenger : public User
{
public:
    Passenger(std::string _name);
};

#endif
