#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"


float PL(float f, float d){
    return 28 + 22 * log10(d) + 20* log10(f);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QGraphicsScene* scene = new QGraphicsScene();
    int maxX = 1366;
    int maxY = 768;
    int onePixDistance = 1000;
    int TxPower = 23;
    int antGain = 10;
    float freq = 2.5;
    int cellPosX = 650;
    int cellPosY = 360;
    QPixmap map(maxX, maxY);
    QPainter p(&map);
    //p.setPen(QColor(255, 0, 0, 255)); // <-- задание цвета
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            float distance = 0;
            distance = sqrt(pow(abs(cellPosX - i),2) + pow(abs(cellPosY - j),2)); // [pix]
            distance *= onePixDistance; // [meters]
            float sigPower = TxPower + antGain - PL(freq, distance);
            //std :: cout<< sigPower<< std :: endl;
            //p.setPen(sigPower_to_color(sigPower));
            if(sigPower > -44 ){
                p.setPen(QColor(255,0,0)); // <-- задание цвета
            }


            else if (sigPower > -84 ) {
                p.setPen(QColor(255,((sigPower+44)*(-1.0)*6.375), 0)); // <-- задание цвета
            }

            else if (sigPower > -104 ) {
                p.setPen(QColor((255+((sigPower+84)*12.75)), 255,0)); // <-- задание цвета
            }
            else if (sigPower > -124 ) {
               p.setPen(QColor(0, 255, ((sigPower+104)*(-1.0)*12.75))); // <-- задание цвета
            }


            else if (sigPower > -144 ) {
                p.setPen(QColor(0, 255+((sigPower+124)*12.75), 255)); // <-- задание цвета
            }
            p.drawPoint(i, j);
        }
    }
    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}


MainWindow::~MainWindow()
{
    delete ui;
}

