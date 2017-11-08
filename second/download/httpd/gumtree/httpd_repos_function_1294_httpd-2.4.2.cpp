static int pointinpoly(const double point[2], double pgon[MAXVERTS][2])
{
    int i, numverts, crossings = 0;
    double x = point[X], y = point[Y];

    for (numverts = 0; pgon[numverts][X] != -1 && numverts < MAXVERTS;
        numverts++) {
        /* just counting the vertexes */
    }

    for (i = 0; i < numverts; i++) {
        double x1=pgon[i][X];
        double y1=pgon[i][Y];
        double x2=pgon[(i + 1) % numverts][X];
        double y2=pgon[(i + 1) % numverts][Y];
        double d=(y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);

        if ((y1 >= y) != (y2 >= y)) {
            crossings +=y2 - y1 >= 0 ? d >= 0 : d <= 0;
        }
        if (!d && fmin(x1,x2) <= x && x <= fmax(x1,x2)
            && fmin(y1,y2) <= y && y <= fmax(y1,y2)) {
            return 1;
        }
    }
    return crossings & 0x01;
}