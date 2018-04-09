//
// Created by David Reis on 04/04/2018.
//

#include "VertexData.h"

VertexData::VertexData(long id, double x, double y, double height)
        : id(id), x(x), y(y), sharePoint(), height(height){}

VertexData::VertexData(long id) : id(id){}

SharePoint &VertexData::getSharePoint() {
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

bool VertexData::operator==(const VertexData& rhs)const{
    return (this->id==rhs.id);
}

double VertexData::getHeight() const {
    return height;
}

void VertexData::setHeight(double height) {
    VertexData::height = height;
}
