    return o;
}

/* Create a string object from a long double. If humanfriendly is non-zero
 * it does not use exponential format and trims trailing zeroes at the end,
 * however this result in loss of precision. Otherwise exp format is used
 * and the output of snprintf() is not modified. */
robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
    char buf[256];
    int len;

