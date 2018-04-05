//
// Created by David Reis on 04/04/2018.
//

#include "VertexData.h"

VertexData::VertexData(long id, double latitudeDegrees, double longitudeDegrees, double latitudeRadians, double longitudeRadians)
        : id(id), latitudeDegrees(latitudeDegrees), longitudeDegrees(longitudeDegrees),
          latitudeRadians(latitudeRadians), longitudeRadians(longitudeRadians), sharePoint() {}

VertexData::VertexData(long id) : id(id){}

const SharePoint &VertexData::getSharePoint() const {
    return sharePoint;
}

void VertexData::setSharePoint(const SharePoint &sharePoint) {
    VertexData::sharePoint = sharePoint;
}

long VertexData::getId() {
    return id;
}

void VertexData::setId(long id) {
    VertexData::id = id;
}

double VertexData::getLatitudeDegrees() const {
    return latitudeDegrees;
}

void VertexData::setLatitudeDegrees(double latitudeDegrees) {
    VertexData::latitudeDegrees = latitudeDegrees;
}

double VertexData::getLongitudeDegrees() const {
    return longitudeDegrees;
}

void VertexData::setLongitudeDegrees(double longitudeDegrees) {
    VertexData::longitudeDegrees = longitudeDegrees;
}

double VertexData::getLatitudeRadians() const {
    return latitudeRadians;
}

void VertexData::setLatitudeRadians(double latitudeRadians) {
    VertexData::latitudeRadians = latitudeRadians;
}

double VertexData::getLongitudeRadians() const {
    return longitudeRadians;
}

void VertexData::setLongitudeRadians(double longitudeRadians) {
    VertexData::longitudeRadians = longitudeRadians;
}

bool VertexData::operator==(const VertexData& rhs)const{
    return (this->id==rhs.id);
}
