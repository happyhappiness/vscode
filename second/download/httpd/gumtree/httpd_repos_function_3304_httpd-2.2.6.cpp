static char *conv_10_quad(widest_int num, register bool_int is_unsigned,
                     register bool_int *is_negative, char *buf_end,
                     register apr_size_t *len)
{
    register char *p = buf_end;
    u_widest_int magnitude;

    /*
     * We see if we can use the faster non-quad version by checking the
     * number against the largest long value it can be. If <=, we
     * punt to the quicker version.
     */
    if (((u_widest_int)num <= (u_widest_int)ULONG_MAX && is_unsigned) 
        || (num <= LONG_MAX && num >= LONG_MIN && !is_unsigned))
            return(conv_10( (wide_int)num, is_unsigned, is_negative,
               buf_end, len));

    if (is_unsigned) {
        magnitude = (u_widest_int) num;
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
            widest_int t = num + 1;

            magnitude = ((u_widest_int) -t) + 1;
        }
        else
            magnitude = (u_widest_int) num;
    }

    /*
     * We use a do-while loop so that we write at least 1 digit 
     */
    do {
        u_widest_int new_magnitude = magnitude / 10;

        *--p = (char) (magnitude - new_magnitude * 10 + '0');
        magnitude = new_magnitude;
    }
    while (magnitude);

    *len = buf_end - p;
    return (p);
}