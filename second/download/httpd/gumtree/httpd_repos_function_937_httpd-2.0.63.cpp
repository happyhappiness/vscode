static int is_closer(const double point[2], double coords[MAXVERTS][2],
                     double *closest)
{
    double dist_squared = ((point[X] - coords[0][X])
                           * (point[X] - coords[0][X]))
                          + ((point[Y] - coords[0][Y])
                             * (point[Y] - coords[0][Y]));

    if (point[X] < 0 || point[Y] < 0) {
        return (0);          /* don't mess around with negative coordinates */
    }

    if (*closest < 0 || dist_squared < *closest) {
        *closest = dist_squared;
        return (1);          /* if this is the first point or is the closest yet
                                set 'closest' equal to this distance^2 */
    }

    return (0);              /* if it's not the first or closest */

}