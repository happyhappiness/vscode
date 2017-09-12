    }
}

/* Check if the nul-terminated string 's' can be represented by a long
 * (that is, is a number that fits into long without any other space or
 * character before or after the digits).
 *
 * If so, the function returns REDIS_OK and *longval is set to the value
 * of the number. Otherwise REDIS_ERR is returned */
static int isStringRepresentableAsLong(char *s, long *longval) {
    char buf[32], *endptr;
    long value;
    int slen;
    
    value = strtol(s, &endptr, 10);
    if (endptr[0] != '\0') return REDIS_ERR;
    slen = snprintf(buf,32,"%ld",value);

    /* If the number converted back into a string is not identical
     * then it's not possible to encode the string as integer */
    if (strlen(buf) != (unsigned)slen || memcmp(buf,s,slen)) return REDIS_ERR;
    if (longval) *longval = value;
    return REDIS_OK;
}

/* Try to encode a string object in order to save space */
static int tryObjectEncoding(robj *o) {
    long value;
    sds s = o->ptr;

    if (o->encoding != REDIS_ENCODING_RAW)
