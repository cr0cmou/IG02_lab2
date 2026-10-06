#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QPen>
#include <QPainter>

class Shape {

public:
    Shape(const QPoint &start, const QPen &pen);
    virtual ~Shape() = default; //virtual because Shape is a base class

    void setEnd(const QPoint &end);
    virtual void draw(QPainter &painter) const = 0; //makes Shape abstract: pure virtual function
    //you can't use the draw() method directly on a Shape that isn't a Rectangle or sth else

protected:
    QPoint start_; //shape start point (x,y)
    QPoint end_; //shape end point (x,y)
    QPen pen_;

};

class Line : public Shape { //Line inherits from abstract base class Shape

public:
    using Shape::Shape; //reuse of the base constructor
    void draw(QPainter &painter) const override; //override of the virtual draw() method -> Line is now non abstract

};

class Rectangle : public Shape { //Rectangle inherits from abstract base class Shape

public:
    using Shape::Shape; //reuse of the base constructor
    void draw(QPainter &painter) const override; //-> Rectangle is now non abstract

};

class Ellipse : public Shape { //Ellpise inherits from abstract base class Shape

public:
    using Shape::Shape; //reuse of the base constructor
    void draw(QPainter &painter) const override; //-> Ellipse is now non abtract

};

enum class ShapeType { Line, Rectangle, Ellipse };

#endif // SHAPE_H
