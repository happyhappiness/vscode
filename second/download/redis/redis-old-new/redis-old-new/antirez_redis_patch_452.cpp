@@ -77,12 +77,12 @@ int getTimeoutFromObjectOrReply(client *c, robj *object, mstime_t *timeout, int
     long long tval;
 
     if (getLongLongFromObjectOrReply(c,object,&tval,
-        "timeout is not an integer or out of range") != REDIS_OK)
-        return REDIS_ERR;
+        "timeout is not an integer or out of range") != C_OK)
+        return C_ERR;
 
     if (tval < 0) {
         addReplyError(c,"timeout is negative");
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (tval > 0) {
@@ -91,7 +91,7 @@ int getTimeoutFromObjectOrReply(client *c, robj *object, mstime_t *timeout, int
     }
     *timeout = tval;
 
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Block a client for the specific operation type. Once the REDIS_BLOCKED