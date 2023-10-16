#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void creat_map();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

double distance(int posX, int i, int posY, int j);
void creat_barrier(float (&mass_sig)[1366][768]);
void Bresenham(int x1, int y1, int x2, int y2, float Lc, float (&mass_sig)[1366][768]);
#endif // MAINWINDOW_H
