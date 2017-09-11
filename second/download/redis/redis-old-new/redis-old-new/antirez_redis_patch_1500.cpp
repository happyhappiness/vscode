@@ -767,7 +767,6 @@ int processMultibulkBuffer(redisClient *c) {
             }
 
             pos += newline-(c->querybuf+pos)+2;
-#ifdef REDIS_MBULK_BIG_ARG
             if (ll >= REDIS_MBULK_BIG_ARG) {
                 /* If we are going to read a large object from network
                  * try to make it likely that it will start at c->querybuf
@@ -780,7 +779,6 @@ int processMultibulkBuffer(redisClient *c) {
              * going to contain. */
             if (ll >= REDIS_MBULK_BIG_ARG)
                 c->querybuf = sdsMakeRoomFor(c->querybuf,ll+2);
-#endif
             c->bulklen = ll;
         }
 
@@ -789,15 +787,13 @@ int processMultibulkBuffer(redisClient *c) {
             /* Not enough data (+2 == trailing \r\n) */
             break;
         } else {
-#ifdef REDIS_MBULK_BIG_ARG
             /* Optimization: if the buffer contanins JUST our bulk element
              * instead of creating a new object by *copying* the sds we
              * just use the current sds string. */
             if (pos == 0 &&
                 c->bulklen >= REDIS_MBULK_BIG_ARG &&
                 (signed) sdslen(c->querybuf) == c->bulklen+2)
             {
-                // printf("HERE (arg %d)\n",c->argc);
                 c->argv[c->argc++] = createObject(REDIS_STRING,c->querybuf);
                 sdsIncrLen(c->querybuf,-2); /* remove CRLF */
                 c->querybuf = sdsempty();
@@ -806,14 +802,10 @@ int processMultibulkBuffer(redisClient *c) {
                 c->querybuf = sdsMakeRoomFor(c->querybuf,c->bulklen+2);
                 pos = 0;
             } else {
-#endif
-                // printf("NOT HERE (arg %d) (pos %d)\n",c->argc, pos);
                 c->argv[c->argc++] =
                     createStringObject(c->querybuf+pos,c->bulklen);
                 pos += c->bulklen+2;
-#ifdef REDIS_MBULK_BIG_ARG
             }
-#endif
             c->bulklen = -1;
             c->multibulklen--;
         }