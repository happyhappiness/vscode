sds catAppendOnlyGenericCommand(sds buf, int argc, robj **argv) {
    int j;
    buf = sdscatprintf(buf,"*%d\r\n",argc);
    for (j = 0; j < argc; j++) {
        robj *o = getDecodedObject(argv[j]);
        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
        buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
        buf = sdscatlen(buf,"\r\n",2);
        decrRefCount(o);
    }
    return buf;
}