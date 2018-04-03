#include "Node.h"

Node :: Node(long id,double latitudeDegrees, double longitudeDegrees, double longitudeRadians, double latitudeRadians)
{
    this->id = id;
    this->latitudeDegrees = latitudeDegrees;
    this->longitudeDegrees = longitudeDegrees;
    this->longitudeRadians = longitudeRadians;
    this->latitudeRadians = latitudeRadians;
}