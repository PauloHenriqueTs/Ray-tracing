#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "util.h"
void printVector(Vector pix_col)
{
    printf("%lf %lf %lf\n", pix_col.x, pix_col.y, pix_col.z);
}

int main()
{
    int nx = 80;
    int ny = 60;
    int d = 2;
    int l = -10;
    int r = 10;
    int b = -10;
    int t = 10;

    Vector img[nx][ny];
    int count = 0;
    Vector p = newVector(0, 0, 0);
    Vector pf = newVector(0, 0, 0);
    Vector e = newVector(2, 2, 1);
    Vector w = normalize(e);
    Vector taux = minVector(w);
    Vector u = normalize(cross(taux, w));
    Vector v = cross(u, w);

    Sphere sphere = newSphere(newVector(10, 10, 2), 10);
    Vector spherecolor = newVector(255, 255, 255);
    Vector black = newVector(0, 0, 0);
    FILE *fp;
    fp = fopen("./test.ppm", "w+");
    fprintf(fp, "P3\n%d %d 255\n", nx, ny);

    for (int j = 1; j <= ny; ++j)
    {
        for (int i = 1; i <= nx; ++i)
        {
            img[i][j] = black;
            double ul = l + (r - l) * (0.5 + i) / nx;
            double vl = b + (((t - b) * (0.5 + j)) / ny);
            Vector origem = e;
            Vector direcao = addVector(multScaleVector(w, -1 * d), addVector(multScaleVector(u, ul), multScaleVector(v, vl)));

            Vector omc = minusVector(origem, sphere.c);
            double x1 = dot(multScaleVector(direcao, 2), omc);
            double x2 = 4 * dot(direcao, direcao);
            double x3 = (dot(omc, omc) - (sphere.r * sphere.r));
            double delta = (x1 * x1) - (x2 * x3);
            if (delta >= 0)
            {
                double domc = dot(direcao, omc);
                double dd = dot(direcao, direcao);
                double t1 = ((-1 * domc) + sqrt(delta)) / dd;
                double t2 = ((-1 * domc) - sqrt(delta)) / dd;

                Vector p1 = addVector(origem, multScaleVector(direcao, t1));

                Vector p2 = addVector(origem, multScaleVector(direcao, t2));

                if (V1moreV2(p1, p2))
                {
                    p = p1;
                }
                else
                {
                    p = p2;
                }

                if (V1moreV2(p, pf))
                {
                    pf = p;
                }
                img[i][j] = spherecolor;
            }

            fprintf(fp, "%d %d %d\n", (u_int8_t)img[i][j].x, (u_int8_t)img[i][j].y, (u_int8_t)img[i][j].z);
        }
    }

    fclose(fp);

    //printf( "%d %d %d\n", (int)pix_col.x, (int)pix_col.y, (int)pix_col.z);

    return 1;
}
