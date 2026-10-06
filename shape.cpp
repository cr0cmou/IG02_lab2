#include <shape.h>

#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QRect>
#include <QPainterPath>
#include <QPainterPathStroker>

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

bool Line::contains(const QPoint &p) const {
    QPainterPath path;
    path.moveTo(start_);
    path.lineTo(end_);

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8); //width of the pen + tolerance
    return stroker.createStroke(path).contains(p); //create visible stroke along the path and check if in intersects with p
}

bool Rectangle::contains(const QPoint &p) const {
    QPainterPath path;
    path.addRect(QRect(start_, end_).normalized());

    /*
    if (path.contains(p)) {
        return true; //if the click is inside the rectangle: shape is selected
    }
    */

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8); //width of the pen + tolerance
    return stroker.createStroke(path).contains(p);
}

bool Ellipse::contains(const QPoint &p) const {
    QPainterPath path;
    path.addEllipse(QRect(start_, end_).normalized());

    /*
    if (path.contains(p)) {
        return true; //if the click is inside the rectangle: shape is selected
    }
    */

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8); //width of the pen + tolerance
    return stroker.createStroke(path).contains(p);
}

void Line::drawSelected(QPainter &painter) const {
    QPainterPath path;
    path.moveTo(start_);
    path.lineTo(end_);

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8);
    stroker.setCapStyle(Qt::RoundCap);
    QPainterPath outline = stroker.createStroke(path);

    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); // -> outline only, no fill

    painter.drawPath(outline);

}

void Rectangle::drawSelected(QPainter &painter) const {
    QPainterPath path;
    path.addRect(QRect(start_, end_).normalized());

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8);
    stroker.setCapStyle(Qt::RoundCap);
    QPainterPath outline = stroker.createStroke(path);

    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); // -> outline only, no fill

    painter.drawPath(outline);
}

void Ellipse::drawSelected(QPainter &painter) const {
    QPainterPath path;
    path.addEllipse(QRect(start_, end_).normalized());

    QPainterPathStroker stroker;
    stroker.setWidth(pen_.width() + 8);
    stroker.setCapStyle(Qt::RoundCap);
    QPainterPath outline = stroker.createStroke(path);

    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);

    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); // -> outline only, no fill

    painter.drawPath(outline);
}