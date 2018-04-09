//
// Created by David Reis on 04/04/2018.
//

#ifndef CAL_VERTEXDATA_H
#define CAL_VERTEXDATA_H


#include "SharePoint.h"

class VertexData {

private:
    SharePoint sharePoint;
    long id;
    double latitudeDegrees;
    double longitudeDegrees;
    double latitudeRadians;
    double longitudeRadians;
    double height;
public:
    double getHeight() const;

    void setHeight(double height);

public:
    VertexData(long id);
    VertexData(long id, double latitudeDegrees, double longitudeDegrees, double latitudeRadians, double longitudeRadians, double height);
    SharePoint &getSharePoint();
    void setSharePoint(const SharePoint &sharePoint);
    long getId();
    void setId(long id);
    double getLatitudeDegrees() const;
    void setLatitudeDegrees(double latitudeDegrees);
    double getLongitudeDegrees() const;
    void setLongitudeDegrees(double longitudeDegrees);
    double getLatitudeRadians() const;
    void setLatitudeRadians(double latitudeRadians);
    double getLongitudeRadians() const;
    void setLongitudeRadians(double longitudeRadians);

    bool operator==(const VertexData& rhs)const;
};


#endif //CAL_VERTEXDATA_H
