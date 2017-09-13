static int fwriteBulk(FILE *fp, robj *obj) {
    char buf[128];
    obj = getDecodedObject(obj);
    snprintf(buf,sizeof(buf),"$%ld\r\n",(long)sdslen(obj->ptr));
    if (fwrite(buf,strlen(buf),1,fp) == 0) goto err;
    if (fwrite(obj->ptr,sdslen(obj->ptr),1,fp) == 0) goto err;
    if (fwrite("\r\n",2,1,fp) == 0) goto err;
    decrRefCount(obj);
    return 1;
err:
    decrRefCount(obj);
    return 0;
}