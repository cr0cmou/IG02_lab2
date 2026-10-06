#include <centralwidget.h>
#include <QPainter>
#include <QPen>
#include <shape.h>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent) { //class constructor
    this->setMinimumSize(500, 500);

}

void CentralWidget::paintEvent(QPaintEvent* event){ //to call whenever the widget needs to repaint itself
    //standard behavior: draws the background
    QWidget::paintEvent(event);

    QPainter painter(this);

    /* USELESS AFTER SECTION 5:
    QPen pen;
    pen.setStyle(lineStyle_);
    pen.setWidth(lineThickness_);
    pen.setBrush(lineColor_);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    //create a painter for this widget:
    painter.setPen(pen);
    //painter.drawLine(150, 0, 250, 500); // (x_start, y_start, x_end, y_end


    if (hasLine_) { //get rid of default 0-length line at the beginning
        painter.drawLine(start_, end_);
    }
    */

    for (auto const &s: shapeBuffer_) { //redraw all old shapes
        s->draw(painter);
    }

    if (current_) {
        current_->draw(painter); //call the draw method depending on the last shape
    }

}

void CentralWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        drawing_ = true;

        QPen pen;
        //setting pen to currently selected variables:
        pen.setColor(lineColor_);
        pen.setWidth(lineThickness_);
        pen.setStyle(lineStyle_);

        switch (shapeType_) { //create a shape with its own copy of a pen -> PERSISTENT
        case ShapeType::Line:
            current_ = std::make_unique<Line>(event->pos(), pen); //std::make_unique manages the memory
            break;
        case ShapeType::Rectangle:
            current_ = std::make_unique<Rectangle>(event->pos(), pen);
            break;
        case ShapeType::Ellipse:
            current_ = std::make_unique<Ellipse>(event->pos(), pen);
        }

        update(); //schedules a paintEvent()
    }
}

void CentralWidget::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing_) { //buttons() returns which buttons are currently held
        current_->setEnd(event->pos()); //no need to check is current_ is a null pointer thanks to drawing_

        update();
    }
}

void CentralWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing_) {
        //hasLine_ = false; //uncomment this line to make the line disappear when releasing mouse button
        drawing_ = false;
        current_->setEnd(event->pos()); //no need to check if current_ is a null pointer thanks to drawing_
        shapeBuffer_.push_back(std::move(current_)); // move last drawn shape from current_ to shapeBuffer_

        update();
    }
}

void CentralWidget::setLineColor(QAction* colorAction) {
    lineColor_ = colorAction->data().value<QColor>(); //data is of type QVariant -> convert it to QColor type
    update();

}

void CentralWidget::setLineThickness(QAction* thicknessAction) {
    lineThickness_ = thicknessAction->data().value<int>(); //QVariant -> int
    update();

}

void CentralWidget::setLineStyle(QAction* styleAction) {
    lineStyle_ = static_cast<Qt::PenStyle>(styleAction->data().value<int>()); //QVariant -> int -> PenStyle
    update();

}

void CentralWidget::setShape(QAction *shapeAction) {
    shapeType_ = static_cast<ShapeType>(shapeAction->data().value<int>());
}

void CentralWidget::enterEditMode(QAction* editAction) {
    //TODO
}