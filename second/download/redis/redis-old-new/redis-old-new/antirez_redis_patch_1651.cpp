@@ -712,6 +712,10 @@ int processMultibulkBuffer(redisClient *c) {
         if (newline == NULL)
             return REDIS_ERR;
 
+        /* Buffer should also contain \n */
+        if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
+            return REDIS_ERR;
+
         /* We know for sure there is a whole line since newline != NULL,
          * so go ahead and find out the multi bulk length. */
         redisAssert(c->querybuf[0] == '*');
@@ -733,37 +737,37 @@ int processMultibulkBuffer(redisClient *c) {
         /* Setup argv array on client structure */
         if (c->argv) zfree(c->argv);
         c->argv = zmalloc(sizeof(robj*)*c->multibulklen);
-
-        /* Search new newline */
-        newline = strchr(c->querybuf+pos,'\r');
     }
 
     redisAssert(c->multibulklen > 0);
     while(c->multibulklen) {
         /* Read bulk length if unknown */
         if (c->bulklen == -1) {
             newline = strchr(c->querybuf+pos,'\r');
-            if (newline != NULL) {
-                if (c->querybuf[pos] != '$') {
-                    addReplyErrorFormat(c,
-                        "Protocol error: expected '$', got '%c'",
-                        c->querybuf[pos]);
-                    setProtocolError(c,pos);
-                    return REDIS_ERR;
-                }
+            if (newline == NULL)
+                break;
 
-                ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
-                if (!ok || ll < 0 || ll > 512*1024*1024) {
-                    addReplyError(c,"Protocol error: invalid bulk length");
-                    setProtocolError(c,pos);
-                    return REDIS_ERR;
-                }
-                pos += newline-(c->querybuf+pos)+2;
-                c->bulklen = ll;
-            } else {
-                /* No newline in current buffer, so wait for more data */
+            /* Buffer should also contain \n */
+            if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
                 break;
+
+            if (c->querybuf[pos] != '$') {
+                addReplyErrorFormat(c,
+                    "Protocol error: expected '$', got '%c'",
+                    c->querybuf[pos]);
+                setProtocolError(c,pos);
+                return REDIS_ERR;
             }
+
+            ok = string2ll(c->querybuf+pos+1,newline-(c->querybuf+pos+1),&ll);
+            if (!ok || ll < 0 || ll > 512*1024*1024) {
+                addReplyError(c,"Protocol error: invalid bulk length");
+                setProtocolError(c,pos);
+                return REDIS_ERR;
+            }
+
+            pos += newline-(c->querybuf+pos)+2;
+            c->bulklen = ll;
         }
 
         /* Read bulk argument */