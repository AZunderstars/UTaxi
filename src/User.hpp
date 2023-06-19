#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

class User
{
public:
    virtual std::string get_name();
    int get_user_type();

protected:
    std::string username;
    int type;
};

#endif
