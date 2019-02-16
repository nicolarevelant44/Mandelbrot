#include <iostream>
#include <fstream>
using namespace std;

struct Color {
    int r;
    int g;
    int b;
};

const int MAX = 400;
const int WIDTH = 1024;
const int HEIGHT = 1024;
const float ZOOM_STEP = 1.5;
const int MIN_ZOOM = 10000;
const int IMAGES = 30;

void Mandelbrot(double, double, double);
Color ColorOf(int);


int main()
{
    double zoom = MIN_ZOOM, tX = 0.31, tY = 0.03;
    for (int i = 0; i < IMAGES; i++)
    {
        Mandelbrot(zoom, tX, tY);
        zoom *= ZOOM_STEP;
    }
    return 0;
}

/*
 Salva su file un frattale di Mandelbrot con zoom e traslazione
 */
void Mandelbrot(double zoom, double tX, double tY)
{
    ofstream imgS;
    int livelli, avanz;
    Color color;
    double realX, realY, xc, yc, xx, yy;
    float halfWidth = WIDTH / 2.0, halfHeight = HEIGHT / 2.0;
    imgS.open("mandelbrot_zoom_" + to_string(zoom) + "_.ppm");
    // intestazione
    imgS << "P3" << endl;
    imgS << WIDTH << " " << HEIGHT << endl << 255 << endl;
    cout << "ELABORAZIONE MANDELBROT ZOOM " << zoom << "\n\n";
    cout << "Aspetta...";
    
    
    // scansione immagine e salvataggio
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // x e y sono fissi da 0 a 1023
            // realX e realY sono variabili
            // in base allo zoom e al traslato
            // xc e xx sono variabili di calcolo
            
            realX = (x - halfWidth) / zoom + tX;
            realY = (y - halfHeight) / zoom + tY;
            
            livelli = 0;
            xc = realX;
            yc = realY;

            // inizio algoritmo
            for (livelli = 0; livelli < MAX; livelli++)
            {
                xx = xc * xc;
                yy = yc * yc;
                if (xx + yy > 4.0) break;
                yc = 2.0 * xc * yc + realY;
                xc = xx - yy + realX;
            }
            // fine algoritmo
            
            color = ColorOf(livelli * 128 / MAX);
            imgS << color.r << " " << color.g << " " << color.b << " ";
        }
        imgS << endl;
        avanz = (y + 1) * 20 / HEIGHT;
        cout << "\rAvanzamento: ";
        for (int i = 0; i < avanz; i++)
        {
            cout << "#";
        }
        //flush(cout);
    }
    cout << "\n\n";
    
    // chiusura stream
    imgS.close();
}

Color ColorOf(int c)
{
    int r, g, b;
    double t = (double)c/(double)MAX;
    Color color;
    
    // algoritmo colore
    r = (int)(9*(1-t)*t*t*t*255);
    g = (int)(15*(1-t)*(1-t)*t*t*255);
    b = (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
    // fine algoritmo colore
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}