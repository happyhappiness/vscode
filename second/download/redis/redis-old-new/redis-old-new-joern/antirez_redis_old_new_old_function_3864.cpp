static int fwriteBulkObject(FILE *fp, robj *obj) {
    char buf[128];
    int decrrc = 0;

    /* Avoid the incr/decr ref count business if possible to help
     * copy-on-write (we are often in a child process when this function
     * is called).
     * Also makes sure that key objects don't get incrRefCount-ed when VM
     * is enabled */
    if (obj->encoding != REDIS_ENCODING_RAW) {
        obj = getDecodedObject(obj);
        decrrc = 1;
    }
    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
    if (sdslen(obj->ptr) && fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0)
        goto err;
    if (fwrite("\r\n",2,1,fp) == 0) goto err;
    if (decrrc) decrRefCount(obj);
    return 1;
err:
    if (decrrc) decrRefCount(obj);
    return 0;
}