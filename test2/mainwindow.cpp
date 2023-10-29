#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"



#include "heat_map.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    map = new Heat_map(int pos_X, int pos_Y, int maxX,int maxY);

}


MainWindow::~MainWindow()
{
    delete ui;
}

