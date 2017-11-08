static double get_y_coord(const char *args)
{
    char *endptr;               /* we want it non-null */
    const char *start_of_y = NULL;
    double y_coord = -1;        /* -1 is returned on error */

    if (args == NULL) {
        return (-1);            /* in case we aren't passed anything */
    }

    start_of_y = ap_strchr_c(args, ',');     /* the comma */

    if (start_of_y) {

        start_of_y++;           /* start looking at the character after
                                   the comma */

        while (*start_of_y && !apr_isdigit(*start_of_y)) {
            start_of_y++;       /* jump to the first digit, but not
                                   past the end */
	}

        y_coord = strtod(start_of_y, &endptr);

        if (endptr > start_of_y) {
            return (y_coord);
	}
    }

    return (-1);                /* if no conversion was made, or
                                   no comma was found in args */
}