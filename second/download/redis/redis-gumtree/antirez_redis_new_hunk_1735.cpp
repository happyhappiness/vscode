
/* Create a string object from a long double. If humanfriendly is non-zero
 * it does not use exponential format and trims trailing zeroes at the end,
 * however this results in loss of precision. Otherwise exp format is used
 * and the output of snprintf() is not modified.
 *
 * The 'humanfriendly' option is used for INCRBYFLOAT and HINCRBYFLOAT. */
robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
    char buf[256];
    int len;

    if (isinf(value)) {
        /* Libc in odd systems (Hi Solaris!) will format infinite in a
         * different way, so better to handle it in an explicit way. */
        if (value > 0) {
            memcpy(buf,"inf",3);
            len = 3;
        } else {
            memcpy(buf,"-inf",4);
            len = 4;
        }
    } else if (humanfriendly) {
        /* We use 17 digits precision since with 128 bit floats that precision
         * after rounding is able to represent most small decimal numbers in a
         * way that is "non surprising" for the user (that is, most small
         * decimal numbers will be represented in a way that when converted
         * back into a string are exactly the same as what the user typed.) */
        len = snprintf(buf,sizeof(buf),"%.17Lf", value);
        /* Now remove trailing zeroes after the '.' */
        if (strchr(buf,'.') != NULL) {
