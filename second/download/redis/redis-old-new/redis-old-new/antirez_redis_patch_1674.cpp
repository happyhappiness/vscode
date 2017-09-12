@@ -127,22 +127,57 @@ void computeDatasetDigest(unsigned char *final) {
                 }
                 setTypeReleaseIterator(si);
             } else if (o->type == REDIS_ZSET) {
-                zset *zs = o->ptr;
-                dictIterator *di = dictGetIterator(zs->dict);
-                dictEntry *de;
+                unsigned char eledigest[20];
 
-                while((de = dictNext(di)) != NULL) {
-                    robj *eleobj = dictGetEntryKey(de);
-                    double *score = dictGetEntryVal(de);
-                    unsigned char eledigest[20];
+                if (o->encoding == REDIS_ENCODING_ZIPLIST) {
+                    unsigned char *zl = o->ptr;
+                    unsigned char *eptr, *sptr;
+                    unsigned char *vstr;
+                    unsigned int vlen;
+                    long long vll;
+                    double score;
 
-                    snprintf(buf,sizeof(buf),"%.17g",*score);
-                    memset(eledigest,0,20);
-                    mixObjectDigest(eledigest,eleobj);
-                    mixDigest(eledigest,buf,strlen(buf));
-                    xorDigest(digest,eledigest,20);
+                    eptr = ziplistIndex(zl,0);
+                    redisAssert(eptr != NULL);
+                    sptr = ziplistNext(zl,eptr);
+                    redisAssert(sptr != NULL);
+
+                    while (eptr != NULL) {
+                        redisAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
+                        score = zzlGetScore(sptr);
+
+                        memset(eledigest,0,20);
+                        if (vstr != NULL) {
+                            mixDigest(eledigest,vstr,vlen);
+                        } else {
+                            ll2string(buf,sizeof(buf),vll);
+                            mixDigest(eledigest,buf,strlen(buf));
+                        }
+
+                        snprintf(buf,sizeof(buf),"%.17g",score);
+                        mixDigest(eledigest,buf,strlen(buf));
+                        xorDigest(digest,eledigest,20);
+                        zzlNext(zl,&eptr,&sptr);
+                    }
+                } else if (o->encoding == REDIS_ENCODING_SKIPLIST) {
+                    zset *zs = o->ptr;
+                    dictIterator *di = dictGetIterator(zs->dict);
+                    dictEntry *de;
+
+                    while((de = dictNext(di)) != NULL) {
+                        robj *eleobj = dictGetEntryKey(de);
+                        double *score = dictGetEntryVal(de);
+
+                        snprintf(buf,sizeof(buf),"%.17g",*score);
+                        memset(eledigest,0,20);
+                        mixObjectDigest(eledigest,eleobj);
+                        mixDigest(eledigest,buf,strlen(buf));
+                        xorDigest(digest,eledigest,20);
+                    }
+                    dictReleaseIterator(di);
+                } else {
+                    redisPanic("Unknown sorted set encoding");
                 }
-                dictReleaseIterator(di);
             } else if (o->type == REDIS_HASH) {
                 hashTypeIterator *hi;
                 robj *obj;