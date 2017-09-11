@@ -1000,8 +1000,10 @@ int processMultibulkBuffer(redisClient *c) {
             newline = strchr(c->querybuf+pos,'\r');
             if (newline == NULL) {
                 if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
-                    addReplyError(c,"Protocol error: too big bulk count string");
+                    addReplyError(c,
+                        "Protocol error: too big bulk count string");
                     setProtocolError(c,0);
+                    return REDIS_ERR;
                 }
                 break;
             }