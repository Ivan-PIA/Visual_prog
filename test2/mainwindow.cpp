#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"



#include "heat_map.h"
#include "map3d.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    char fn_sig[] = "signal.png";
    scene = new QGraphicsScene();
    map = new Heat_map();
    map ->Lossing();
    map->Propag_loss();
    map ->Draw_map(fn_sig);

    //setCentralWidget(map->Get_View());
    Map3D *map3d = new Map3D(150, 50, 800, 800, 1000, 1000);
    //this -> layout()->addWidget(map->Get_View());
    this->layout()->addWidget(map3d->get_container());
    map3d->render(fn_sig);

}


MainWindow::~MainWindow()
{
    delete ui;
}

