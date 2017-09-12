                }
                setTypeReleaseIterator(si);
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
                hashTypeIterator *hi;
                robj *obj;
