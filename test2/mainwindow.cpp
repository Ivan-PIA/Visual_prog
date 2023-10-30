#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"



#include "heat_map.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    Heat_map *map = new Heat_map(1200,1000);

    QGraphicsScene* scene = new QGraphicsScene();


    map ->dB_to_color(map->Get_maxX(),map->Get_maxY(),map->Get_pos_X(),map->Get_pos_Y(),map->Get_PowerSig_map());
    map->Draw_map(map->Get_PowerSig_map());
    setCentralWidget(map->Get_View());

}


MainWindow::~MainWindow()
{
    delete ui;
}

