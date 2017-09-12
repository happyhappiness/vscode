@@ -3487,16 +3487,13 @@ static robj *rdbLoadObject(int type, FILE *fp) {
         o = createZsetObject();
         zs = o->ptr;
         /* Load every single element of the list/set */
-        redisLog(REDIS_DEBUG,"SORTED SET LEN: %zu\n", zsetlen);
         while(zsetlen--) {
             robj *ele;
             double *score = zmalloc(sizeof(double));
 
             if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
-            redisLog(REDIS_DEBUG,"ele %s (%d) (%d)\n", (char*)ele->ptr, ftell(fp), zsetlen);
             tryObjectEncoding(ele);
             if (rdbLoadDoubleValue(fp,score) == -1) return NULL;
-            redisLog(REDIS_DEBUG,"score %.17g\n", *score);
             dictAdd(zs->dict,ele,score);
             zslInsert(zs->zsl,*score,ele);
             incrRefCount(ele); /* added to skiplist */
@@ -3544,7 +3541,6 @@ static robj *rdbLoadObject(int type, FILE *fp) {
     } else {
         redisAssert(0 != 0);
     }
-    redisLog(REDIS_DEBUG,"DONE\n");
     return o;
 }
 
@@ -3599,7 +3595,6 @@ static int rdbLoad(char *filename) {
         }
         /* Read key */
         if ((keyobj = rdbLoadStringObject(fp)) == NULL) goto eoferr;
-        redisLog(REDIS_DEBUG,"KEY: %s\n", (char*)keyobj->ptr);
         /* Read value */
         if ((o = rdbLoadObject(type,fp)) == NULL) goto eoferr;
         /* Add the new object in the hash table */
@@ -3934,7 +3929,7 @@ static void substrCommand(redisClient *c) {
             rangelen = (end-start)+1;
 
             /* Return the result */
-            addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",rangelen));
+            addReplySds(c,sdscatprintf(sdsempty(),"$%zu\r\n",rangelen));
             range = sdsnewlen((char*)o->ptr+start,rangelen);
             addReplySds(c,range);
             addReply(c,shared.crlf);
@@ -7215,6 +7210,7 @@ static int syncWithMaster(void) {
             "temp-%d.%ld.rdb",(int)time(NULL),(long int)getpid());
         dfd = open(tmpfile,O_CREAT|O_WRONLY|O_EXCL,0644);
         if (dfd != -1) break;
+        sleep(1);
     }
     if (dfd == -1) {
         close(fd);