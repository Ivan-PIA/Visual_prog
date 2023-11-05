#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"



#include "heat_map.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new QGraphicsScene();
    map = new Heat_map();
    map ->Lossing();
    map->Propag_loss();
    map ->Draw_map();

    setCentralWidget(map->Get_View());
    //this -> layout()->addWidget(map->Get_View());

}


MainWindow::~MainWindow()
{
    delete ui;
}

