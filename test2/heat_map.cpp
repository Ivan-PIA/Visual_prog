#include "heat_map.h"
#include "material.h"


Heat_map::Heat_map()
{

    map = new QPixmap(maxX, maxY);

    scene = new QGraphicsScene();

    PowerSig_map = new double*[maxX];
    for (int i=0; i < maxX; i++){
        PowerSig_map[maxX] = new double[maxY];
    }
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
int Heat_map::Get_onePixDistance(){
    return onePixDistance;
}

int Heat_map::Get_freq(){
    return freq;
}

QGraphicsView *Heat_map::Get_View(){
    return view;
}
double Heat_map ::distance(int posX, int i, int posY, int j){
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
                mass_sig[i][j] = 11.0;
            }
            if  ( i > 700 and j>600 and i < 750 and j < 620){
                mass_sig[i][j] = 12.0;
            }
            if  ( i > 650 and j>500 and i < 700 and j < 520){
                mass_sig[i][j] = 13.0;
            }

}

double Heat_map::Bresenham(int x1, int y1, int x2, int y2,double **mass_sig){
    double Lg = Get_Glass(freq);
    double Lg_r = Get_Glass_IRR(freq);
    double Lc = Get_Concrete(freq);
    double Lw = Get_Wood(freq);
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
                    sum_loss+=Lg;
                }
                else if (mass_sig[x1][y1]==11.0 )
                {
                    sum_loss+=Lg_r;
                }
                else if (mass_sig[x1][y1]==12.0 )
                {
                    sum_loss+=Lc;
                }
                else if (mass_sig[x1][y1]==13.0 )
                {
                    sum_loss+=Lw;
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


void Heat_map::Lossing(){

    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){

            double dist = distance(pos_X,i,pos_Y,j);
            dist *= onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, dist);
            PowerSig_map[i][j]=sigPower;
            creat_barrier(i, j, PowerSig_map);
        }

    }
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){

           Bresenham(pos_X,pos_Y,i,j,PowerSig_map);
        }
    }
}

void Heat_map :: Draw_map(){

    QPainter p(pixmap);
    for(int i = 0; i < maxX; i++){
        for(int j = 0; j < maxY; j++){
            if(PowerSig_map[i][j] > -44  ){
                p.setPen(QColor(255,0,0)); // <-- задание цвета
            }

            else if (PowerSig_map[i][j] > -84 ) {
                p.setPen(QColor(255,((PowerSig_map[i][j]+44)*(-1.0)*6.375), 0)); // <-- задание цвета
            }
            else if (PowerSig_map[i][j] > -104 ) {
                p.setPen(QColor((255+((PowerSig_map[i][j]+84)*12.75)), 255,0)); // <-- задание цвета
            }
            else if (PowerSig_map[i][j] > -124 ) {
               p.setPen(QColor(0, 255, ((PowerSig_map[i][j]+104)*(-1.0)*12.75))); // <-- задание цвета
            }
            else if (PowerSig_map[i][j] > -144 ) {
                //temp = 255+((mass_sigPower[i][j]+124)*12.75);
                p.setPen(QColor(0, 255+((PowerSig_map[i][j]+124)*12.75), 255)); // <-- задание цвета
            }


            if(PowerSig_map[i][j] == 10.0){
                p.setPen(QColor(0,0,0));
            }
            p.drawPoint(i, j);
        }
    }

    p.end();



}

Heat_map::~Heat_map(){



    delete pixmap;
    delete view;
    delete scene;
}
