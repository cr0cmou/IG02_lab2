#include <shape.h>

#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QRect>

// MARIAM PINTON

Shape::Shape(const QPoint &start, const QPen &pen) {
    start_ = start;
    end_ = start; //by default, the end is the same as the start
    pen_ = pen;
}

void Shape::setEnd(const QPoint &end) {
    end_ = end;
}

void Line::draw(QPainter &painter) const {
    painter.setPen(pen_);
    painter.drawLine(start_, end_);
}

void Rectangle::draw(QPainter &painter) const {
    painter.setPen(pen_);
    QRect rect = QRect(start_, end_).normalized();
    painter.drawRect(rect);
}

void Ellipse::draw(QPainter &painter) const {
    painter.setPen(pen_);
    QRect rect = QRect(start_, end_).normalized();
    painter.drawEllipse(rect);

}