    return 0;
}

static int rdbSaveStringObject(FILE *fp, robj *obj) {
    size_t len = sdslen(obj->ptr);

    if (rdbSaveLen(fp,len) == -1) return -1;
    if (len && fwrite(obj->ptr,len,1,fp) == 0) return -1;
    return 0;
