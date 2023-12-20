#ifndef MAP3D_H
#define MAP3D_H


#include <iostream>

#include <QtDataVisualization/Q3DTheme>
#include <QtDataVisualization/QCustom3DItem>
#include <QtDataVisualization/QCustom3DLabel>
#include <QtGui/QImage>

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtCore/QPropertyAnimation>


using namespace QtDataVisualization;

class QWidget;

class Map3D : public QObject
{
public:
    Map3D(int pos_x, int pos_y, int size_x, int size_y, int size_map_x, int size_map_y);
    QWidget *get_container();
    void render(char *file_texture);
    QSurface3DSeries *get_QSurface3DSeries();
    Q3DSurface *graph;
private:
    int pos_x, pos_y;
    int size_x, size_y;
    int size_map_x, size_map_y;
    QWidget *container;
    QSurface3DSeries *layerOneSeries;
    char filename[FILENAME_MAX] = "../photo/map_heights.png";
};


#endif // MAP3D_H
