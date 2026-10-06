#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QCloseEvent>
#include <centralwidget.h>

// MARIAM PINTON

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow //create a new class MainWindow that inherits from QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void openFile();
    void saveFile();
    void quitApp1();
    void quitApp2();
    void quitApp3();

private:
    Ui::MainWindow *ui;
    QTextEdit* text;
    CentralWidget* drawingBoard;

protected:
    void closeEvent(QCloseEvent* event) override;
    QActionGroup* createColorMenu();
    QActionGroup* createThicknessMenu();
    QActionGroup* createStyleMenu();
    QActionGroup* createShapeMenu();
};
#endif // MAINWINDOW_H
