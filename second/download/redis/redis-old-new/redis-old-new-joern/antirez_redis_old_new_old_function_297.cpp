void *rdbLoadLzfStringObject(rio *rdb, int flags, size_t *lenptr) {
    int plain = flags & RDB_LOAD_PLAIN;
    int sds = flags & RDB_LOAD_SDS;
    uint64_t len, clen;
    unsigned char *c = NULL;
    char *val = NULL;

    if ((clen = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
    if ((len = rdbLoadLen(rdb,NULL)) == RDB_LENERR) return NULL;
    if ((c = zmalloc(clen)) == NULL) goto err;

    /* Allocate our target according to the uncompressed size. */
    if (plain) {
        val = zmalloc(len);
        if (lenptr) *lenptr = len;
    } else {
        val = sdsnewlen(NULL,len);
    }

    /* Load the compressed representation and uncompress it to target. */
    if (rioRead(rdb,c,clen) == 0) goto err;
    if (lzf_decompress(c,clen,val,len) == 0) goto err;
    zfree(c);

    if (plain || sds) {
        return val;
    } else {
        return createObject(OBJ_STRING,val);
    }
err:
    zfree(c);
    if (plain)
        zfree(val);
    else
        sdsfree(val);
    return NULL;
}