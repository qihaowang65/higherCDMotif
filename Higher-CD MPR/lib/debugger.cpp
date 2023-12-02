#include "debugger.h"

Debugger::Debugger(){}

Debugger::~Debugger(){}

void Debugger::Check(){
    cout << "CheckPoint: " << counter << endl;
    counter++;
    return;
}

