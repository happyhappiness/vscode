    return l;
}

/* Check if the sds string 's' can be represented by a long long
 * (that is, is a number that fits into long without any other space or
 * character before or after the digits, so that converting this number
 * back to a string will result in the same bytes as the original string).
 *
 * If so, the function returns REDIS_OK and *llongval is set to the value
 * of the number. Otherwise REDIS_ERR is returned */
int isStringRepresentableAsLongLong(sds s, long long *llongval) {
    char buf[32], *endptr;
    long long value;
    int slen;

    value = strtoll(s, &endptr, 10);
    if (endptr[0] != '\0') return REDIS_ERR;
    slen = ll2string(buf,32,value);

    /* If the number converted back into a string is not identical
     * then it's not possible to encode the string as integer */
    if (sdslen(s) != (unsigned)slen || memcmp(buf,s,slen)) return REDIS_ERR;
    if (llongval) *llongval = value;
    return REDIS_OK;
}

int isStringRepresentableAsLong(sds s, long *longval) {
    long long ll;

    if (isStringRepresentableAsLongLong(s,&ll) == REDIS_ERR) return REDIS_ERR;
    if (ll < LONG_MIN || ll > LONG_MAX) return REDIS_ERR;
    *longval = (long)ll;
    return REDIS_OK;
}

int isObjectRepresentableAsLongLong(robj *o, long long *llongval) {
    redisAssert(o->type == REDIS_STRING);
    if (o->encoding == REDIS_ENCODING_INT) {
        if (llongval) *llongval = (long) o->ptr;
        return REDIS_OK;
    } else {
        return isStringRepresentableAsLongLong(o->ptr,llongval);
    }
}
