static double get_x_coord(const char *args)
{
    char *endptr;               /* we want it non-null */
    double x_coord = -1;        /* -1 is returned if no coordinate is given */

    if (args == NULL) {
        return (-1);            /* in case we aren't passed anything */
    }

    while (*args && !apr_isdigit(*args) && *args != ',') {
        args++;                 /* jump to the first digit, but not past
                                   a comma or end */
    }

    x_coord = strtod(args, &endptr);

    if (endptr > args) {        /* if a conversion was made */
        return (x_coord);
    }

    return (-1);                /* else if no conversion was made,
                                   or if no args was given */
}