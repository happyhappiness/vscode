static char *conv_10(register apr_int32_t num, register int is_unsigned,
                     register int *is_negative, char *buf_end,
                     register apr_size_t *len)
{
    register char *p = buf_end;
    register apr_uint32_t magnitude = num;

    if (is_unsigned) {
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
            apr_int32_t t = num + 1;
            magnitude = ((apr_uint32_t) -t) + 1;
        }
    }

    /*
     * We use a do-while loop so that we write at least 1 digit 
     */
    do {
        register apr_uint32_t new_magnitude = magnitude / 10;

        *--p = (char) (magnitude - new_magnitude * 10 + '0');
        magnitude = new_magnitude;
    }
    while (magnitude);

    *len = buf_end - p;
    return (p);
}