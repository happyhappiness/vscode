@@ -3820,7 +3820,7 @@ static void keysCommand(redisClient *c) {
     dictEntry *de;
     sds pattern = c->argv[1]->ptr;
     int plen = sdslen(pattern);
-    unsigned long numkeys = 0, keyslen = 0;
+    unsigned long numkeys = 0;
     robj *lenobj = createObject(REDIS_STRING,NULL);
 
     di = dictGetIterator(c->db->dict);
@@ -3833,17 +3833,15 @@ static void keysCommand(redisClient *c) {
         if ((pattern[0] == '*' && pattern[1] == '\0') ||
             stringmatchlen(pattern,plen,key,sdslen(key),0)) {
             if (expireIfNeeded(c->db,keyobj) == 0) {
-                if (numkeys != 0)
-                    addReply(c,shared.space);
+                addReplyBulkLen(c,keyobj);
                 addReply(c,keyobj);
+                addReply(c,shared.crlf);
                 numkeys++;
-                keyslen += sdslen(key);
             }
         }
     }
     dictReleaseIterator(di);
-    lenobj->ptr = sdscatprintf(sdsempty(),"$%lu\r\n",keyslen+(numkeys ? (numkeys-1) : 0));
-    addReply(c,shared.crlf);
+    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
 }
 
 static void dbsizeCommand(redisClient *c) {