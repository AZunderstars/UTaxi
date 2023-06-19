#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__

#include "User.hpp"
#include "consts.hpp"
#include <string>

class Driver : public User
{
public:
    Driver(std::string _name);
};
#endif
