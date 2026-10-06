#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <shape.h>

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QKeySequence>
#include <QToolBar>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPushButton>
#include <QCloseEvent>
#include <centralwidget.h>
#include <QActionGroup>
#include <QPen>

// MARIAM PINTON

MainWindow::MainWindow(QWidget *parent) //class constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QMenuBar* myMenuBar = this->menuBar();
    QMenu* myMenu = myMenuBar->addMenu("File");

    QToolBar* myToolBar = this->addToolBar("File");

    QAction* openAction = new QAction(QIcon(":/icons/images/open.png"), "Open", this);
    openAction->setShortcut(QKeySequence("Ctrl+O"));
    openAction->setToolTip("Open File");
    myMenu->addAction(openAction);
    myToolBar->addAction(openAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);

    QAction* saveAction = new QAction(QIcon(":/icons/images/save.png"), "Save", this);
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setToolTip("Save File");
    myMenu->addAction(saveAction);
    myToolBar->addAction(saveAction);

    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    QAction* quitAction = new QAction(QIcon(":/icons/images/quit.png"), "Quit", this);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setToolTip("Quit App");
    myMenu->addAction(quitAction);
    myToolBar->addAction(quitAction);

    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp3); //WARNING: if wiring with quitApp1 or quitApp2, the dialog box will appear twice

    /*
    this->text = new QTextEdit(this);
    this->setCentralWidget(text);
    */

    this->drawingBoard = new CentralWidget(this);
    this->setCentralWidget(drawingBoard);

    //ui->setupUi(this);
    QStatusBar* myStatusBar = statusBar();
    myStatusBar->showMessage("Status Bar Test");

    QToolBar* drawingToolBar = this->addToolBar("Drawing Tools");

    QActionGroup* colorActionGroup = createColorMenu(); //see below
    drawingToolBar->addActions(colorActionGroup->actions());
    connect(colorActionGroup, &QActionGroup::triggered, this->drawingBoard, &CentralWidget::setLineColor);

    QActionGroup* thicknessActionGroup = createThicknessMenu(); //see below
    drawingToolBar->addActions(thicknessActionGroup->actions());
    connect(thicknessActionGroup, &QActionGroup::triggered, this->drawingBoard, &CentralWidget::setLineThickness);

    QActionGroup* styleActionGroup = createStyleMenu(); //see below
    drawingToolBar->addActions(styleActionGroup->actions());
    connect(styleActionGroup, &QActionGroup::triggered, this->drawingBoard, &CentralWidget::setLineStyle);

    QActionGroup* shapeActionGroup = createShapeMenu(); //see below
    drawingToolBar->addActions(shapeActionGroup->actions());
    connect(shapeActionGroup, &QActionGroup::triggered, this->drawingBoard, &CentralWidget::setShape);

    QAction* editAction = new QAction("edit", this);
    editAction->setCheckable(true);
    drawingToolBar->addAction(editAction);
    connect(editAction, &QAction::triggered, this->drawingBoard, &CentralWidget::enterEditMode);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    //qDebug() << "openFile()";
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "/home/mariam/TELECOM/4IG02/IG02_lab1/", "Text files (*.txt)");
    qDebug() << fileName;
    if (fileName.isEmpty())
        return;

    QFile file(fileName); //create a QFile object pointing to the path obtained from the dialog box
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QString content = out.readAll();
        //qDebug() << content;

        this->text->setHtml(content); //this->text : variable d'instance de type QTextEdit*
        file.close();
    }

}

void MainWindow::saveFile() {
    //qDebug() << "saveFile()";
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "/home/mariam/TELECOM/4IG02/IG02_lab1/", "Text files (*.txt)");
    qDebug() << fileName;
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        qDebug() << this->text->toPlainText();
        out << this->text->toPlainText();
        file.close();
    }
}

void MainWindow::quitApp1() { //VERSION 1: using QMessageBox's in-built methods
    //qDebug() << "quitApp()";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quit App", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No);
    //the question() method calls exec()is  internally, and returns the result of the clicked button as a StandardButton value

    if (reply == QMessageBox::Yes) {
        qApp->quit(); //the quit() method creates a QCloseEvent that is handled by the closeEvent() method
    }

}

void MainWindow::quitApp2() { //VERSION 2: building the buttons and message box manually
    //constructor: QMessageBox(QMessageBox::Icon icon, QString &title, QString &text, QMessageBox::StandardButtons buttons, QWidget* parent, flags)
    QMessageBox quitBox(QMessageBox::Question, "Quit App", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No, this);
    //quitBox.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum); //doesn't work
    int result = quitBox.exec(); //exec() function returns an int

    if (result == QMessageBox::Yes) { //implicit conversion: QMessageBox::Yes is a possible value from the enum StandardButton (NoButton, Ok, Yes, No...)
        qApp->quit(); //the quit() method creates a QCloseEvent that is handled by the closeEvent() method
    }

}

void MainWindow::quitApp3() { //VERSION 3: the dialog box is handled by the closeEvent method
    qApp->quit(); //the quit() method creates a QCloseEvent that is handled by the closeEvent() method
}

void MainWindow::closeEvent(QCloseEvent *event) { //override of the closeEvent method
    qDebug() << "closeEvent() method";
    //constructor: QMessageBox(QMessageBox::Icon icon, QString &title, QString &text, QMessageBox::StandardButtons buttons, QWidget* parent, flags)
    QMessageBox quitBox(QMessageBox::Question, "Quit App", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::No, this);
    //quitBox.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum); //doesn't work
    int result = quitBox.exec(); //exec() method returns an int

    if (result == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }

}

QActionGroup* MainWindow::createColorMenu() {
    QActionGroup* colorActionGroup = new QActionGroup(this);
    colorActionGroup->setExclusive(true); //the colors are mutually exclusive


    const QList<QPair<QString, QColor>> colors = {
        {"black", Qt::black},
        {"red", Qt::red},
        {"green", Qt::green},
        {"blue", Qt::blue}
    };

    for (const auto &c: colors) {
        QAction* action = colorActionGroup->addAction(c.first);
        action->setCheckable(true);
        action->setData(c.second);
        if (c.first == "black") {
            action->setChecked(true); //the default pen is black
        }
    }

    return colorActionGroup;

}

QActionGroup* MainWindow::createThicknessMenu() {
    QActionGroup* thicknessActionGroup = new QActionGroup(this);
    thicknessActionGroup->setExclusive(true);

    const QList<QPair<QString, int>> thicknesses = {
        {"thick", 15},
        {"thin", 3}
    };

    for (const auto &t: thicknesses) {
        QAction* action = thicknessActionGroup->addAction(t.first);
        action->setCheckable(true);
        action->setData(t.second);
        if (t.first == "thick") {
            action->setChecked(true); //the default pen is thick
        }
    }

    return thicknessActionGroup;
}

QActionGroup* MainWindow::createStyleMenu() {
    QActionGroup* styleActionGroup = new QActionGroup(this);
    styleActionGroup->setExclusive(true);

    const QList<QPair<QString, Qt::PenStyle>> styles = {
        {"solid", Qt::SolidLine},
        {"dotted", Qt::DotLine}
    };

    for (const auto &s: styles) {
        QAction* action = styleActionGroup->addAction(s.first);
        action->setCheckable(true);
        action->setData(static_cast<int>(s.second)); //Qt::PenStyle -> int for compiling
        if (s.first == "solid") {
            action->setChecked(true); //the default pen is solid line
        }
    }

    return styleActionGroup;

}

QActionGroup* MainWindow::createShapeMenu() {
    QActionGroup* shapeActionGroup = new QActionGroup(this);
    shapeActionGroup->setExclusive(true);

    const QList<QPair<QString, ShapeType>> shapes = { //Shapes are defined in shape.cpp / shape.h
        {"line", ShapeType::Line},
        {"rectangle", ShapeType::Rectangle},
        {"ellipse", ShapeType::Ellipse}
    };

    for (const auto &s: shapes) {
        QAction* action = shapeActionGroup->addAction(s.first);
        action->setCheckable(true);
        action->setData(static_cast<int>(s.second));
        if (s.first == "line") {
            action->setChecked(true);
        }
    }

    return shapeActionGroup;

}
