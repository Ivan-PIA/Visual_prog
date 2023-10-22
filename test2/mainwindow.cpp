#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cmath>
#include "QPainter"





float PL(float f, float d){
    return 28 + 22 * log10(d) + 20* log10(f);
}

double distance(int posX, int i, int posY, int j){
    return sqrt(pow(abs(posX - i),2) + pow(abs(posY - j),2));
}



void creat_barrier(int i, int j, float (&mass_sig)[1366][768]){
            if  ( i > 1000 and j > 350 and i < 1015 and j < 650){
                mass_sig[i][j] = 10.0;
            }
            if  ( i > 100 and j>500 and i < 400 and j < 550){
                mass_sig[i][j] = 10.0;
            }
            if  ( i > 700 and j>600 and i < 750 and j < 620){
                mass_sig[i][j] = 10.0;
            }

}


float Bresenham(int x1, int y1, int x2, int y2,float (&mass_sig)[1366][768]){
    float Lg = (2 + 0.2*2.4)/10;
    float sum_loss = 0;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

        int error = deltaX - deltaY;
        if (mass_sig[x2][y2] < 0.0){

            do
            {

                //if  ( x1 > 700 and y1>600 and x1 < 750 and y1 < 620)
               // if  ( x1 > 100 and y1>500 and x1 < 400 and y1 < 550)
               // {
                    //printf("%f ",mass_sig[x1][y1]);
                //}

                if (mass_sig[x1][y1]==10.0 )     // на этом сравнении начинает с 700
                {
                     printf("x-%d y-%d ", x2, y2);
                    sum_loss+=Lg;//
                }
                int error2 = error * 2;
                if(error2 > -deltaY)
                {
                    error -= deltaY;
                    x1 += signX;
                }
                if(error2 < deltaX)
                {
                    error += deltaX;
                    y1 += signY;
                }


            }while(x1 != x2 || y1 != y2);

            // if ( sum_loss >0 )
            // printf("%f  - %d %d ", sum_loss, x1, y1); // не считает сумму лосов у первой фигуры

        mass_sig[x2][y2]-=sum_loss;
        }

        return sum_loss;
}

void MainWindow::creat_map(){

    QGraphicsScene* scene = new QGraphicsScene();
    int maxX = 1366;
    int maxY = 768;
    int onePixDistance = 10;
    int TxPower = 23;
    int antGain = 6;
    float freq = 2.4;
    int posX = 650;
    int posY = 360;
    float temp;
    QPixmap map(maxX, maxY);
    QPainter p(&map);
    float mass_sigPower[1366][768];

    //float Lg = 2 + 0.2*freq;
    //float Lc = 5 + 4.0*freq;

    //mass_sigPower = create_mass(maxX, maxY);

    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){

            double dist = distance(posX,i,posY,j);
            dist *= onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, dist);
            mass_sigPower[i][j]=sigPower;
            creat_barrier(i, j, mass_sigPower);
            //printf("%f ",mass_sigPower[i][j]);
            //if (mass_sigPower[i][j]==10.0){
                //printf("x-%d y-%d ", i, j);
            //}
            Bresenham(posX,posY,i,j,mass_sigPower);
            //if (mass_sigPower[i][j]==10.0){
                //printf("x-%d y-%d ", i, j);
            //}
            //if  ( i > 700 and j>600 and i < 750 and j < 620){
                //printf("%f ", bres);
            //}
            //std :: cout<< sigPower<< std :: endl;
            //p.setPen(sigPower_to_color(sigPower));

            if(mass_sigPower[i][j] > -44  ){
                p.setPen(QColor(255,0,0)); // <-- задание цвета
            }

            else if (mass_sigPower[i][j] > -84 ) {
                p.setPen(QColor(255,((mass_sigPower[i][j]+44)*(-1.0)*6.375), 0)); // <-- задание цвета
            }
            else if (mass_sigPower[i][j] > -104 ) {
                p.setPen(QColor((255+((mass_sigPower[i][j]+84)*12.75)), 255,0)); // <-- задание цвета
            }
            else if (mass_sigPower[i][j] > -124 ) {
               p.setPen(QColor(0, 255, ((mass_sigPower[i][j]+104)*(-1.0)*12.75))); // <-- задание цвета
            }
            else if (mass_sigPower[i][j] > -144 ) {
                //temp = 255+((mass_sigPower[i][j]+124)*12.75);
                p.setPen(QColor(0, 255+((mass_sigPower[i][j]+124)*12.75), 255)); // <-- задание цвета
            }



            if(mass_sigPower[i][j] == 10.0){
                p.setPen(QColor(0,0,0));

            }
            //printf("%f ",temp);
/*
            if  ( i > 300 and j>200 and i < 400 and j < 230){
                p.setPen(QColor(0,0,0));
            }
            if  ( i > 700 and j>600 and i < 750 and j < 620){
                p.setPen(QColor(0,0,0));
            }
            if  ( i > 1000 and j > 350 and i < 1015 and j < 650){
                p.setPen(QColor(0,0,0));
            }*/

            p.drawPoint(i, j);
        }
    }
    printf("%f  ",mass_sigPower[0][0]);
    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    creat_map();
}


MainWindow::~MainWindow()
{
    delete ui;
}

