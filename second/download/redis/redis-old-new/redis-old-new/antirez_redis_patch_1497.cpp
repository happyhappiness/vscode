@@ -94,13 +94,13 @@ void computeDatasetDigest(unsigned char *final) {
             time_t expiretime;
 
             memset(digest,0,20); /* This key-val digest */
-            key = dictGetEntryKey(de);
+            key = dictGetKey(de);
             keyobj = createStringObject(key,sdslen(key));
 
             mixDigest(digest,key,sdslen(key));
 
             /* Make sure the key is loaded if VM is active */
-            o = dictGetEntryVal(de);
+            o = dictGetVal(de);
 
             aux = htonl(o->type);
             mixDigest(digest,&aux,sizeof(aux));
@@ -165,8 +165,8 @@ void computeDatasetDigest(unsigned char *final) {
                     dictEntry *de;
 
                     while((de = dictNext(di)) != NULL) {
-                        robj *eleobj = dictGetEntryKey(de);
-                        double *score = dictGetEntryVal(de);
+                        robj *eleobj = dictGetKey(de);
+                        double *score = dictGetVal(de);
 
                         snprintf(buf,sizeof(buf),"%.17g",*score);
                         memset(eledigest,0,20);
@@ -244,7 +244,7 @@ void debugCommand(redisClient *c) {
             addReply(c,shared.nokeyerr);
             return;
         }
-        val = dictGetEntryVal(de);
+        val = dictGetVal(de);
         strenc = strEncoding(val->encoding);
 
         addReplyStatusFormat(c,