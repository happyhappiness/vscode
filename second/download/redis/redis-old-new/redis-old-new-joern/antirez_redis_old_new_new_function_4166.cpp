static void genericHgetallCommand(redisClient *c, int flags) {
    robj *o, *lenobj;
    unsigned long count = 0;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL
        || checkType(c,o,REDIS_HASH)) return;

    lenobj = createObject(REDIS_STRING,NULL);
    addReply(c,lenobj);
    decrRefCount(lenobj);

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *p = zipmapRewind(o->ptr);
        unsigned char *field, *val;
        unsigned int flen, vlen;

        while((p = zipmapNext(p,&field,&flen,&val,&vlen)) != NULL) {
            robj *aux;

            if (flags & REDIS_GETALL_KEYS) {
                aux = createStringObject((char*)field,flen);
                addReplyBulk(c,aux);
                decrRefCount(aux);
                count++;
            }
            if (flags & REDIS_GETALL_VALS) {
                aux = createStringObject((char*)val,vlen);
                addReplyBulk(c,aux);
                decrRefCount(aux);
                count++;
            }
        }
    } else {
        dictIterator *di = dictGetIterator(o->ptr);
        dictEntry *de;

        while((de = dictNext(di)) != NULL) {
            robj *fieldobj = dictGetEntryKey(de);
            robj *valobj = dictGetEntryVal(de);

            if (flags & REDIS_GETALL_KEYS) {
                addReplyBulk(c,fieldobj);
                count++;
            }
            if (flags & REDIS_GETALL_VALS) {
                addReplyBulk(c,valobj);
                count++;
            }
        }
        dictReleaseIterator(di);
    }
    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
}