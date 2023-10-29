#ifndef HEAT_MAP_H
#define HEAT_MAP_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>

class QColor;

class Heat_map
{
public:
    Heat_map(int pos_X, int pos_Y, int maxX,int maxY);
    void dB_to_color(int maxX, int maxY, int posX, int posY, double **PowerSig_map);
    double Bresenham(int x1, int y1, int x2, int y2,double **PowerSig_map);
    double distance(int posX, int i, int posY, int j);
    void Draw_map(double **PowerSig_map);


private:
    int pos_X = 650 , pos_Y = 360, maxX = 1300, maxY = 800;
    double **PowerSig_map;

    int onePixDistance = 10;
    int TxPower = 23;
    int antGain = 6;
    float freq = 2.4;
    QPixmap *pixmap;
    QGraphicsScene* scene;
    QGraphicsView *view;

};

#endif // HEAT_MAP_H
