static int pointinrect(const double point[2], double coords[MAXVERTS][2])
{
    double max[2], min[2];
    if (coords[0][X] > coords[1][X]) {
        max[0] = coords[0][X];
        min[0] = coords[1][X];
    }
    else {
        max[0] = coords[1][X];
        min[0] = coords[0][X];
    }

    if (coords[0][Y] > coords[1][Y]) {
        max[1] = coords[0][Y];
        min[1] = coords[1][Y];
    }
    else {
        max[1] = coords[1][Y];
        min[1] = coords[0][Y];
    }

    return ((point[X] >= min[0] && point[X] <= max[0]) &&
            (point[Y] >= min[1] && point[Y] <= max[1]));
}