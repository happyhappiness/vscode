         maxidx = 2; minidx = 3;
     } else {
         /* Range is given as [min,max] */
         minidx = 2; maxidx = 3;
     }
 
-    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
+    if (zslParseLexRange(c->argv[minidx],c->argv[maxidx],&range) != C_OK) {
         addReplyError(c,"min or max not valid string range item");
         return;
     }
 
     /* Parse optional extra arguments. Note that ZCOUNT will exactly have
      * 4 arguments, so we'll never enter the following code path. */
     if (c->argc > 4) {
         int remaining = c->argc - 4;
         int pos = 4;
 
         while (remaining) {
             if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
-                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != REDIS_OK) ||
-                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != REDIS_OK)) return;
+                if ((getLongFromObjectOrReply(c, c->argv[pos+1], &offset, NULL) != C_OK) ||
+                    (getLongFromObjectOrReply(c, c->argv[pos+2], &limit, NULL) != C_OK)) return;
                 pos += 3; remaining -= 3;
             } else {
                 zslFreeLexRange(&range);
                 addReply(c,shared.syntaxerr);
                 return;
             }
         }
     }
 
     /* Ok, lookup the key and get the range */
     if ((zobj = lookupKeyReadOrReply(c,key,shared.emptymultibulk)) == NULL ||
-        checkType(c,zobj,REDIS_ZSET))
+        checkType(c,zobj,OBJ_ZSET))
     {
         zslFreeLexRange(&range);
         return;
     }
 
-    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
+    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
         unsigned char *zl = zobj->ptr;
         unsigned char *eptr, *sptr;
         unsigned char *vstr;
         unsigned int vlen;
         long long vlong;
 
