/*
 * This program save IMAGES Mandelbrot's fractals on PPM format
 * Questo programma salva IMAGES frattali di Mandelbrot in formato PPM
 */

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Color {
    int r;
    int g;
    int b;
};
Color color;

const int MAX = 500;
const int WIDTH = 500;
const int HEIGHT = 500;
const float ZOOM_STEP = 1.2;
const long double MIN_ZOOM = 20000000;
const int IMAGES = 20;
const string PATH = "MB/";

bool Mandelbrot(long double, long double, long double);
Color ColorOf(int);


int main()
{
    long double zoom = MIN_ZOOM, tX = -0.203637665486886, tY = 0.837731935118791;
    for (int i = 0; i < IMAGES; i++)
    {
        cout << "ELABORAZIONE MANDELBROT " << i+1 << "/" << IMAGES << " ZOOM " << to_string(zoom) << "\n\n";
        cout << "Aspetta...";
        if (!Mandelbrot(zoom, tX, tY)) return -1;
        zoom *= ZOOM_STEP;
    }
    return 0;
}

/*
 Salva su file un frattale di Mandelbrot con zoom e traslazione
 */
bool Mandelbrot(long double zoom, long double tX, long double tY)
{
    ofstream imgS;
    string fileName;
    int livelli, avanz;
    Color color;
    long double realX, realY, xc, yc, xx, yy;
    float halfWidth = WIDTH / 2.0, halfHeight = HEIGHT / 2.0;
    fileName = PATH + "M_" + to_string(WIDTH) + "_" + to_string(HEIGHT) + "_zoom_" + to_string(zoom) + "_.ppm";
    imgS.open(fileName);
    if (!imgS.is_open())
    {
        cout << "\rERRORE CREAZIONE FILE " << fileName << "\n";
        return false;
    }
    // intestazione
    imgS << "P3" << endl << WIDTH << " " << HEIGHT << endl << 255 << endl;
    
    
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
            realY = (y - halfHeight) / zoom - tY;
            xc = realX;
            yc = realY;

            // inizio algoritmo
            for (livelli = 0; livelli < MAX; livelli++)
            {
                xx = xc * xc;
                yy = yc * yc;
                if (xx + yy > 4) break;
                yc = 2.0 * xc * yc + realY;
                xc = xx - yy + realX;
            }
            // fine algoritmo
            
            color = ColorOf(livelli);
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
    return true;
}

Color ColorOf(int c)
{
    double t = (double)c / (double)MAX;
    
    // algoritmo colore
    color.r = 9*(1-t)*t*t*t*255;
    color.g = 15*(1-t)*(1-t)*t*t*255;
    color.b = 8.5*(1-t)*(1-t)*(1-t)*t*255;
    // fine algoritmo colore
    
    return color;
}