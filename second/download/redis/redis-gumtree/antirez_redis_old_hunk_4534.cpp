    }
}

static robj *rdbLoadStringObject(FILE*fp,int rdbver) {
    uint32_t len = rdbLoadLen(fp,rdbver);
    sds val;

    if (len == REDIS_RDB_LENERR) return NULL;
    val = sdsnewlen(NULL,len);
    if (len && fread(val,len,1,fp) == 0) {
