@@ -720,13 +720,14 @@ int processMultibulkBuffer(redisClient *c) {
             addReplyError(c,"Protocol error: invalid multibulk length");
             setProtocolError(c,pos);
             return REDIS_ERR;
-        } else {
-            pos = (newline-c->querybuf)+2;
-            if (ll <= 0) {
-                c->querybuf = sdsrange(c->querybuf,pos,-1);
-                return REDIS_OK;
-            }
         }
+
+        pos = (newline-c->querybuf)+2;
+        if (ll <= 0) {
+            c->querybuf = sdsrange(c->querybuf,pos,-1);
+            return REDIS_OK;
+        }
+
         c->multibulklen = ll;
 
         /* Setup argv array on client structure */