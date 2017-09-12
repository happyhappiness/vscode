    return 0;
}

/* String objects in the form "2391" "-100" without any space and with a
 * range of values that can fit in an 8, 16 or 32 bit signed value can be
 * encoded as integers to save space */
int rdbTryIntegerEncoding(sds s, unsigned char *enc) {
    long long value;
    char *endptr, buf[32];

    /* Check if it's possible to encode this value as a number */
    value = strtoll(s, &endptr, 10);
    if (endptr[0] != '\0') return 0;
    snprintf(buf,32,"%lld",value);

    /* If the number converted back into a string is not identical
     * then it's not possible to encode the string as integer */
    if (strlen(buf) != sdslen(s) || memcmp(buf,s,sdslen(s))) return 0;

    /* Finally check if it fits in our ranges */
    if (value >= -(1<<7) && value <= (1<<7)-1) {
        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT8;
        enc[1] = value&0xFF;
        return 2;
    } else if (value >= -(1<<15) && value <= (1<<15)-1) {
        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT16;
        enc[1] = value&0xFF;
        enc[2] = (value>>8)&0xFF;
        return 3;
    } else if (value >= -((long long)1<<31) && value <= ((long long)1<<31)-1) {
        enc[0] = (REDIS_RDB_ENCVAL<<6)|REDIS_RDB_ENC_INT32;
        enc[1] = value&0xFF;
        enc[2] = (value>>8)&0xFF;
        enc[3] = (value>>16)&0xFF;
        enc[4] = (value>>24)&0xFF;
        return 5;
    } else {
        return 0;
    }
}

/* Save a string objet as [len][data] on disk. If the object is a string
 * representation of an integer value we try to safe it in a special form */
static int rdbSaveStringObject(FILE *fp, robj *obj) {
    size_t len = sdslen(obj->ptr);
    int enclen;

    if (len <= 11) {
        unsigned char buf[5];
        if ((enclen = rdbTryIntegerEncoding(obj->ptr,buf)) > 0) {
            if (fwrite(buf,enclen,1,fp) == 0) return -1;
            return 0;
        }
    }
    if (rdbSaveLen(fp,len) == -1) return -1;
    if (len && fwrite(obj->ptr,len,1,fp) == 0) return -1;
    return 0;
