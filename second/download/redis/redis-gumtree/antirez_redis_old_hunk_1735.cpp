
/* Create a string object from a long double. If humanfriendly is non-zero
 * it does not use exponential format and trims trailing zeroes at the end,
 * however this result in loss of precision. Otherwise exp format is used
 * and the output of snprintf() is not modified. */
robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
    char buf[256];
    int len;

    /* We use 17 digits precision since with 128 bit floats that precision
     * after rounding is able to represent most small decimal numbers in a way
     * that is "non surprising" for the user (that is, most small decimal
     * numbers will be represented in a way that when converted back into
     * a string are exactly the same as what the user typed.) */
    if (humanfriendly) {
        len = snprintf(buf,sizeof(buf),"%.17Lf", value);
        /* Now remove trailing zeroes after the '.' */
        if (strchr(buf,'.') != NULL) {
