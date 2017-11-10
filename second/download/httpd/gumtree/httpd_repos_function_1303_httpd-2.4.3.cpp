static int pointincircle(const double point[2], double coords[MAXVERTS][2])
{
    double radius1, radius2;

    radius1 = ((coords[0][Y] - coords[1][Y]) * (coords[0][Y] - coords[1][Y]))
        + ((coords[0][X] - coords[1][X]) * (coords[0][X] - coords[1][X]));

    radius2 = ((coords[0][Y] - point[Y]) * (coords[0][Y] - point[Y]))
        + ((coords[0][X] - point[X]) * (coords[0][X] - point[X]));

    return (radius2 <= radius1);
}