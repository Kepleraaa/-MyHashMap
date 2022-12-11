/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "OurHashMap.h"
using namespace std;

int main()
{
    OurHashMap<int,string> om;
    cout<<"om.isEmpty() "<<om.isEmpty()<<endl;
    om.put(1,"god");
    om.put(2,"physics");
    om.put(3,"yep");
    cout<<"om.put(1,\"god\")"<<endl;
    cout<<"om.put(2,\"physics\")"<<endl;
    cout<<"om.put(3,\"yep\")"<<endl;
    cout<<"om.keys() "<<om.keys()<<endl;
    cout<<"om.values() "<<om.values()<<endl;
    cout<<"om.isEmpty() "<<om.isEmpty()<<endl;
    cout<<"om.size() "<<om.size()<<endl;
    cout<<"om.containsKey(4) "<<om.containsKey(4)<<endl;
    cout<<"om.containsKey(3) "<<om.containsKey(3)<<endl;
    om[4]="math";
    cout<<"om[4]=\"math\""<<endl;
    om.remove(2);
    cout<<"om.remove(2) "<<endl;
    cout<<"om.keys() "<<om.keys()<<endl;
    cout<<"om.values() "<<om.values()<<endl;

    OurHashMap<int,string> om1(om);
    cout<<"OurMap<int,string> om1(om)"<<endl;
    om1.put(4,"hhh");
    om1.put(5,"thx");
    cout<<"om1.put(4,\"hhh\")"<<endl;
    cout<<"om1.keys() "<<om1.keys()<<endl;
    cout<<"om1.values() "<<om1.values()<<endl;

    return 0;
}
