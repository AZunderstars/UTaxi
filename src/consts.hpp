#ifndef __CONSTS_HPP__
#define __CONSTS_HPP__
#include <string>
const std::string WAITING = "waiting",
                  OUTPUT_SEPERATOR = " ",
                  CANCELED = "canceled",
                  TRAVELING = "traveling",
                  FINISHED = "finished",
                  POST = "POST",
                  GET = "GET",
                  DELETE = "DELETE",
                  SIGNUP = "signup",
                  TRIPS = "trips",
                  ACCEPT = "accept",
                  FINISH = "finish",
                  USERNAME = "username",
                  ROLE = "role",
                  DRIVER = "driver",
                  PASSENGER = "passenger",
                  ORIGIN = "origin",
                  DESTINATION = "destination",
                  ID = "id",
                  EMPTY = "EMPTY\n",
                  OK = "OK\n",
                  BAD_REQUEST = "Bad Request",
                  NOT_FOUND = "Not Found",
                  PERMISSION_DENIED = "Permission Denied",
                  EMPTY_STRING = "",
                  IN_HURRY = "in_hurry",
                  SORT_BY_STRING = "sort_by_cost",
                  COST = "cost";

const char FILE_INPUT_SEPERATOR = ',',
           TERMINAL_INPUT_SEPERATOR = ' ',
           NULL_CHAR = '\0';

const int TRIP_STARTING_INDEX = 1,
          PASSENGER_TYPE = 1,
          DRIVER_TYPE = 0,
          NAME_INDEX = 0,
          LATITUDE_INDEX = 1,
          LONGITUDE_INDEX = 2,
          TRAFFIC_INDEX = 3,
          DEFAULT_ID = -1;

const double DIST_CONST = 110.5,
             PRIMARY_COST = 10000,
             HURRY_FACTOR = 1.2;

#endif
