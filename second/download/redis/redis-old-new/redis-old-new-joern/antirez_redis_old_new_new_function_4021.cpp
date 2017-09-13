static void computeDatasetDigest(unsigned char *final) {
    unsigned char digest[20];
    char buf[128];
    dictIterator *di = NULL;
    dictEntry *de;
    int j;
    uint32_t aux;

    memset(final,0,20); /* Start with a clean result */

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;

        if (dictSize(db->dict) == 0) continue;
        di = dictGetIterator(db->dict);

        /* hash the DB id, so the same dataset moved in a different
         * DB will lead to a different digest */
        aux = htonl(j);
        mixDigest(final,&aux,sizeof(aux));

        /* Iterate this DB writing every entry */
        while((de = dictNext(di)) != NULL) {
            robj *key, *o;
            time_t expiretime;

            memset(digest,0,20); /* This key-val digest */
            key = dictGetEntryKey(de);
            mixObjectDigest(digest,key);
            if (!server.vm_enabled || key->storage == REDIS_VM_MEMORY ||
                key->storage == REDIS_VM_SWAPPING) {
                o = dictGetEntryVal(de);
                incrRefCount(o);
            } else {
                o = vmPreviewObject(key);
            }
            aux = htonl(o->type);
            mixDigest(digest,&aux,sizeof(aux));
            expiretime = getExpire(db,key);

            /* Save the key and associated value */
            if (o->type == REDIS_STRING) {
                mixObjectDigest(digest,o);
            } else if (o->type == REDIS_LIST) {
                list *list = o->ptr;
                listNode *ln;
                listIter li;

                listRewind(list,&li);
                while((ln = listNext(&li))) {
                    robj *eleobj = listNodeValue(ln);

                    mixObjectDigest(digest,eleobj);
                }
            } else if (o->type == REDIS_SET) {
                dict *set = o->ptr;
                dictIterator *di = dictGetIterator(set);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    robj *eleobj = dictGetEntryKey(de);

                    xorObjectDigest(digest,eleobj);
                }
                dictReleaseIterator(di);
            } else if (o->type == REDIS_ZSET) {
                zset *zs = o->ptr;
                dictIterator *di = dictGetIterator(zs->dict);
                dictEntry *de;

                while((de = dictNext(di)) != NULL) {
                    robj *eleobj = dictGetEntryKey(de);
                    double *score = dictGetEntryVal(de);
                    unsigned char eledigest[20];

                    snprintf(buf,sizeof(buf),"%.17g",*score);
                    memset(eledigest,0,20);
                    mixObjectDigest(eledigest,eleobj);
                    mixDigest(eledigest,buf,strlen(buf));
                    xorDigest(digest,eledigest,20);
                }
                dictReleaseIterator(di);
            } else if (o->type == REDIS_HASH) {
                hashIterator *hi;
                robj *obj;

                hi = hashInitIterator(o);
                while (hashNext(hi) != REDIS_ERR) {
                    unsigned char eledigest[20];

                    memset(eledigest,0,20);
                    obj = hashCurrent(hi,REDIS_HASH_KEY);
                    mixObjectDigest(eledigest,obj);
                    decrRefCount(obj);
                    obj = hashCurrent(hi,REDIS_HASH_VALUE);
                    mixObjectDigest(eledigest,obj);
                    decrRefCount(obj);
                    xorDigest(digest,eledigest,20);
                }
                hashReleaseIterator(hi);
            } else {
                redisPanic("Unknown object type");
            }
            decrRefCount(o);
            /* If the key has an expire, add it to the mix */
            if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
            /* We can finally xor the key-val digest to the final digest */
            xorDigest(final,digest,20);
        }
        dictReleaseIterator(di);
    }
}