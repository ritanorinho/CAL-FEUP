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

    double height;
public:
    double getHeight() const;
    double x;
    double y;
    void setHeight(double height);

public:
    VertexData(long id);
    VertexData(long id, double x, double y, double height);
    SharePoint &getSharePoint();
    void setSharePoint(const SharePoint &sharePoint);
    long getId();
    void setId(long id);

    bool operator==(const VertexData& rhs)const;
};


#endif //CAL_VERTEXDATA_H
