static char *conv_10(register wide_int num, register bool_int is_unsigned,
                     register bool_int *is_negative, char *buf_end,
                     register int *len)
{
    register char *p = buf_end;
    register u_wide_int magnitude;

    if (is_unsigned) {
        magnitude = (u_wide_int) num;
        *is_negative = FALSE;
    }
    else {
        *is_negative = (num < 0);

        /*
         * On a 2's complement machine, negating the most negative integer 
         * results in a number that cannot be represented as a signed integer.
         * Here is what we do to obtain the number's magnitude:
         *      a. add 1 to the number
         *      b. negate it (becomes positive)
         *      c. convert it to unsigned
         *      d. add 1
         */
        if (*is_negative) {
            wide_int t = num + 1;

            magnitude = ((u_wide_int) -t) + 1;
        }
        else
            magnitude = (u_wide_int) num;
    }

    /*
     * We use a do-while loop so that we write at least 1 digit 
     */
    do {
        register u_wide_int new_magnitude = magnitude / 10;

        *--p = (char) (magnitude - new_magnitude * 10 + '0');
        magnitude = new_magnitude;
    }
    while (magnitude);

    *len = buf_end - p;
    return (p);
}