 * On error -1 is returned.
 * On success if the key was actaully saved 1 is returned, otherwise 0
 * is returned (the key was already expired). */
int rdbSaveKeyValuePair(FILE *fp, robj *key, robj *val,
                        time_t expiretime, time_t now)
{
    int vtype;

    /* Save the expire time */
    if (expiretime != -1) {
        /* If this key is already expired skip it */
        if (expiretime < now) return 0;
        if (rdbSaveType(fp,REDIS_EXPIRETIME) == -1) return -1;
        if (rdbSaveTime(fp,expiretime) == -1) return -1;
    }
    /* Fix the object type if needed, to support saving zipmaps, ziplists,
     * and intsets, directly as blobs of bytes: they are already serialized. */
    vtype = val->type;
    if (vtype == REDIS_HASH && val->encoding == REDIS_ENCODING_ZIPMAP)
        vtype = REDIS_HASH_ZIPMAP;
    else if (vtype == REDIS_LIST && val->encoding == REDIS_ENCODING_ZIPLIST)
        vtype = REDIS_LIST_ZIPLIST;
    else if (vtype == REDIS_SET && val->encoding == REDIS_ENCODING_INTSET)
        vtype = REDIS_SET_INTSET;
    else if (vtype == REDIS_ZSET && val->encoding == REDIS_ENCODING_ZIPLIST)
        vtype = REDIS_ZSET_ZIPLIST;
    /* Save type, key, value */
    if (rdbSaveType(fp,vtype) == -1) return -1;
    if (rdbSaveStringObject(fp,key) == -1) return -1;
    if (rdbSaveObject(fp,val) == -1) return -1;
    return 1;
}

/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
int rdbSave(char *filename) {
    dictIterator *di = NULL;
    dictEntry *de;
    FILE *fp;
    char tmpfile[256];
    int j;
    time_t now = time(NULL);

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
