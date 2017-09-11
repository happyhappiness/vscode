}

/* Convert a double to a string representation. Returns the number of bytes
 * required. The representation should always be parsable by strtod(3).
 * This function does not support human-friendly formatting like ld2string
 * does. It is intented mainly to be used inside t_zset.c when writing scores
 * into a ziplist representing a sorted set. */
int d2string(char *buf, size_t len, double value) {
    if (isnan(value)) {
        len = snprintf(buf,len,"nan");
