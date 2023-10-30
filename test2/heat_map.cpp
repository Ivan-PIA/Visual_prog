#include "heat_map.h"



Heat_map::Heat_map(int maxX,int maxY )
{
    QGraphicsScene* scene = new QGraphicsScene();
    PowerSig_map = new double*[maxX];
    for (int i=0; i < maxX; i++){
        PowerSig_map[maxX] = new double[maxY];
    }

    pixmap = new QPixmap(maxX, maxY);

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);



}
double** Heat_map::Get_PowerSig_map(){
    return PowerSig_map;
}

int Heat_map::Get_maxX(){
    return maxX;
}
int Heat_map::Get_maxY(){
    return maxY;
}
int Heat_map::Get_pos_X(){
    return pos_X;
}
int Heat_map::Get_pos_Y(){
    return pos_Y;
}

QGraphicsView* Heat_map::Get_View(){
    return view;
}

double distance(int posX, int i, int posY, int j){
    return sqrt(pow(abs(posX - i),2) + pow(abs(posY - j),2));
}

float PL(float f, float d){
    return 28 + 22 * log10(d) + 20* log10(f);
}

void creat_barrier(int i, int j, double **mass_sig){
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

double Bresenham(int x1, int y1, int x2, int y2,double **mass_sig){
    double Lg = (2 + 0.2*2.4)/10;
    double sum_loss = 0;
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

        int error = deltaX - deltaY;
        if (mass_sig[x2][y2] < 0.0){

            while(x1 != x2 || y1 != y2)
            {

                if (mass_sig[x1][y1]==10.0 )
                {
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

            }
        mass_sig[x2][y2]-=sum_loss;
        }
        return sum_loss;
}


void Heat_map::dB_to_color(int maxX, int maxY, int posX, int posY, double **mass_sigPower){
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){

            double dist = distance(posX,i,posY,j);
            dist *= onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, dist);
            mass_sigPower[i][j]=sigPower;
            creat_barrier(i, j, mass_sigPower);
        }

    }
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){

            Bresenham(posX,posY,i,j,mass_sigPower);
        }
    }
}

void Heat_map :: Draw_map(double **mass_sigPower){

    QPainter p(pixmap);
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
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
            p.drawPoint(i, j);
        }
    }

    p.end();



}
