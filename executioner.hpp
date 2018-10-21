#ifndef _EXECUTIONER_HPP
#define _EXECUTIONER_HPP

#include <string>

using namespace std;

typedef struct _turnon{
    string print;
    string action;
}Turnon;

typedef struct _condition{
    string object;
    string status;
}Condition;

typedef struct _border{
    string direction;
    string name;
}Border;

typedef struct _status{
    string object;
    string status;
}Status;

typedef struct _owner{
    string object;
    string has;
    string owner;
}Owner;

#endif //_EXECUTIONER_HPP
