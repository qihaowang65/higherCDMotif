#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <iostream>

using namespace std;
class Debugger{
    public:
        Debugger();
        ~Debugger();
        void Check();
    private:
        int counter = 0;
};


#endif