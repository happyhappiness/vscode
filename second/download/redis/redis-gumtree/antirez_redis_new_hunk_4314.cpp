/* Write an object into a file in the bulk format $<count>\r\n<payload>\r\n */
static int fwriteBulk(FILE *fp, robj *obj) {
    char buf[128];
    int decrrc = 0;

    if (obj->storage == REDIS_VM_MEMORY && obj->encoding != REDIS_ENCODING_RAW){
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

