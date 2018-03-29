#ifndef PROJECT1_SUBROAD_H
#define PROJECT1_SUBROAD_H

#include <string>
using namespace std;

//road_id;node1_id;node2_id

class SubRoad{
private:
public:
	int id;
	int node1_id;
	int node2_id;
	
	
	SubRoad() {}
	SubRoad(int id, int node1_id, int node2_id);

};

#endif //PROJECT1_SUBROAD_H

