#ifndef PROJECT1_ROAD_H
#define PROJECT1_ROAD_H

#include <string>
using namespace std;

//road_id;road_name;is_two_way{yes/no}

class Road{
private:
/*    int id;
    string name;
    bool isTwoWay;*/
public:
    int id;
    string name;
    bool isTwoWay;
    Road(){}
    Road(int id,string name, bool isTwoWay);

};

#endif //PROJECT1_ROAD_H
