 * On error -1 is returned.
 * On success if the key was actaully saved 1 is returned, otherwise 0
 * is returned (the key was already expired). */
int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
                        time_t expiretime, time_t now)
{
    /* Save the expire time */
    if (expiretime != -1) {
        /* If this key is already expired skip it */
        if (expiretime < now) return 0;
        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EXPIRETIME) == -1) return -1;
        if (rdbSaveTime(rdb,expiretime) == -1) return -1;
    }

    /* Save type, key, value */
    if (rdbSaveObjectType(rdb,val) == -1) return -1;
    if (rdbSaveStringObject(rdb,key) == -1) return -1;
    if (rdbSaveObject(rdb,val) == -1) return -1;
    return 1;
}

/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
int rdbSave(char *filename) {
    dictIterator *di = NULL;
    dictEntry *de;
    char tmpfile[256];
    int j;
    time_t now = time(NULL);
    FILE *fp;
    rio rdb;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w");
