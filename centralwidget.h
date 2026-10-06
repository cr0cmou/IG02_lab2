#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <shape.h>
#include <memory>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPen>
#include <QList>

//MARIAM PINTON

class CentralWidget : public QWidget { //class CentralWidget inherits from QWidget

    Q_OBJECT

public:
    explicit CentralWidget(QWidget* parent);

public slots:
    void setLineColor(QAction* colorAction);
    void setLineThickness(QAction* thicknessAction);
    void setLineStyle(QAction* styleAction);
    void setShape(QAction* shapeAction);
    void enterEditMode(QAction* editAction);


private:
    //these 3 variables are now useless (Step5) since each Shape contains its own points
    //QPoint start_; //default: (0,0)
    //QPoint end_; //default: (0,0)
    //bool hasLine_ = false; //to avoid having a line drawn when starting the app

    std::unique_ptr<Shape> current_; // pointer to the Shape being drawn
    std::vector<std::unique_ptr<Shape>> shapeBuffer_; // buffer of all drawn shapes
    bool drawing_ = false; //flag to differentiate from other mouseMoveEvents

    QColor lineColor_ = Qt::black; //default
    int lineThickness_ = 15; //default (thick)
    Qt::PenStyle lineStyle_ = Qt::SolidLine; //default
    ShapeType shapeType_ = ShapeType::Line; //default



protected:
    virtual void paintEvent(QPaintEvent *event); //override
    void mousePressEvent(QMouseEvent* event); //override
    void mouseMoveEvent(QMouseEvent* event); //override
    void mouseReleaseEvent(QMouseEvent* event); //override
};

#endif // CENTRALWIDGET_H
