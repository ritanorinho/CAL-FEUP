#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H

//node_id;latitude_in_degrees;longitude_in_degrees;longitude_in_radians;latitude_in_radians

class Node{
private:
/*    int id;
    double latitudeDegrees;
    double latitudeRadians;
    double longitudeDegrees;
    double longitudeRadians;*/
public:
    long id;
    double latitudeDegrees;
    double latitudeRadians;
    double longitudeDegrees;
    double longitudeRadians;
    Node(){}
    Node(long id,double latitudeDegrees, double longitudeDegrees, double longitudeRadians, double latitudeRadians);

    //Helper attributes for Dijkstra search
    double dist;
    Node *path;
    int queueIndex;
};

#endif //PROJECT1_NODE_H
