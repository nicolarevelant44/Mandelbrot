#include <iostream>
#include <fstream>
using namespace std;

struct Color {
    int r;
    int g;
    int b;
};

const int MAX = 2000;
const int WIDTH = 512;
const int HEIGHT = 512;
const float ZOOM_STEP = 1.5;
const int MIN_ZOOM = 1000;
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
    if (c >= 128) // MAX = 128
    {
        r = 0;
        g = 0;
        b = 0;
    }
    else if (c == 0)
    {
        r = 255;
        g = 0;
        b = 0;
    }
    else if (c < 16)
    {
        // 1 - 15
        r = 16 * (16 - c);
        g = 0;
        b = 16 * c - 1;
    }
    else if (c < 32)
    {
        // 16 - 31
        r = 0;
        g = 16 * (c - 16);
        b = 16 * (32 - c) - 1;
    }
    else if (c < 64)
    {
        // 32 - 63
        r = 8 * (c - 32);
        g = 8 * (64 - c) - 1;
        b = 0;
    }
    else
    {
        // 64 - 127
        r = 255 - (c - 64);
        g = 0;
        b = 0;
    }
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}