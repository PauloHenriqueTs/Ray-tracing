#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "util.h"

int main(int argc, char **argv)
{
    // tamanho imagem
    int nx = 800;
    int ny = 600;
    // distancia focal
    int d = 2;
    // ajuste de enquadramento
    int l = 10;
    int r = -10;
    int b = -10;
    int t = 10;

    // inicializa o vetor da imagem
    Vector img;
    // inicializa o ponto do objeto
    Vector p = newVector(0, 0, 0);
    // inicializa o vetor de origem
    Vector e = newVector(10, 10, -50);
    // gera as bases ortonormais
    //Figura 1
    Vector w = normalize(e);
    Vector taux = minVector(w);
    Vector u = normalize(cross(taux, w));
    Vector v = cross(u, w);

    // inicializa esfera (origem, raio)
    Sphere sphere = newSphere(newVector(10, 10, 2), 40);
    // inicializa cor da esfera
    Vector spherecolor = newVector(255, 0, 0);

    // cores auxiliares
    Vector white = newVector(255, 255, 255);
    Vector black = newVector(0, 0, 0);
    //ponto da luz
    Vector luz = newVector(0, 100, 50);

    // coeficiente de reflexao do ambiente do material
    // o quantidade de luz que o objeto reflete
    double ka = 0.5;

    //  coeficiente de difusao
    // quanto maior o valor maior o brilho do objeto
    // ka + kd <= 1 para se manter a lei da conservaçao da energia
    // Figura difusa
    double kd = 0.5;

    // coeficente especular
    // nivel de espalhamento da luz
    // ver figura especular  e = pzin
    double ks = 0.25;
    double pzin = 5;

    FILE *fp;
    fp = fopen("./test.ppm", "w+");
    fprintf(fp, "P3\n%d %d 255\n", nx, ny);

    for (int j = 0; j < ny; j++)
    {
        for (int i = 0; i < nx; i++)
        {
            img = black;
            // Figura caso obliguo
            double ul = l + (r - l) * (0.5 + i) / nx;
            double vl = b + (((t - b) * (0.5 + j)) / ny);
            Vector origem = e;
            Vector direcao = addVector(multScaleVector(w, -1 * d), addVector(multScaleVector(u, ul), multScaleVector(v, vl)));

            // Figura equaçao esfera
            Vector omc = minusVector(origem, sphere.c);
            double x1 = dot(multScaleVector(direcao, 2), omc);
            double x2 = 4 * dot(direcao, direcao);
            double x3 = (dot(omc, omc) - (sphere.r * sphere.r));
            double delta = (x1 * x1) - (x2 * x3);
            if (delta >= 0)
            {
                double coefLuz = 0;
                double domc = dot(direcao, omc);
                double dd = dot(direcao, direcao);
                double t1 = ((-1 * domc) + sqrt(delta)) / dd;
                double t2 = ((-1 * domc) - sqrt(delta)) / dd;

                // Ver Figura esfera interserçao
                if (t1 > t2)
                {
                    p = addVector(origem, multScaleVector(direcao, t1));
                }
                else
                {
                    p = addVector(origem, multScaleVector(direcao, t2));
                }

                // Ver figura luz
                Vector n = divScaleVector(minusVector(p, sphere.c), sphere.r);
                Vector L = normalize(minusVector(luz, p));
                Vector N = normalize(n);
                Vector V = normalize(minusVector(e, p));
                Vector H = normalize(addVector(V, L));
                double dotNL = dot(N, L);
                double dotNH = dot(N, H);
                coefLuz = kd * 255 * dotNL + ks * 255 * pow(dotNH, pzin);
                img = addScaleVector(multScaleVector(spherecolor, ka), coefLuz);

                // funçao para manter os valores das cores ate 255
                img = clamp255(img);
            }

            fprintf(fp, "%d %d %d\n", (int)img.x, (int)img.y, (int)img.z);
        }
    }

    fclose(fp);

    return 1;
}
