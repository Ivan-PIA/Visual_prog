#ifndef HEAT_MAP_H
#define HEAT_MAP_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtWidgets>

class QColor;

class Heat_map
{
    QPainter p;
    QPixmap *map;
    QPixmap *pixmap;
    QGraphicsScene* scene;
    QGraphicsView *view;

    public:
        Heat_map();
        void Lossing();
        double Bresenham(int x1, int y1, int x2, int y2,double **PowerSig_map);
        double distance(int posX, int i, int posY, int j);
        void Draw_map();
        double ** Get_PowerSig_map();
        int Get_maxX();
        int Get_maxY();
        int Get_pos_Y();
        int Get_pos_X();
        int Get_onePixDistance();
        int Get_freq();
        QGraphicsView *Get_View();
        ~Heat_map();


    private:
        int pos_X = 650 , pos_Y = 360, maxX = 1300, maxY = 800;
        double **PowerSig_map;

        int onePixDistance = 10;
        int TxPower = 23;
        int antGain = 6;
        float freq = 2.4;


};

#endif // HEAT_MAP_H
