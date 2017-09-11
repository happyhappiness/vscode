@@ -464,7 +464,9 @@ int isHLLObjectOrReply(redisClient *c, robj *o) {
     /* If this is a string representing an HLL, the size should match
      * exactly. */
     if (stringObjectLen(o) != REDIS_HLL_SIZE) {
-        addReplyErrorFormat(c, "Key is not a valid HyperLogLog string value.");
+        addReplySds(c,
+            sdsnew("-WRONGTYPE Key is not a valid "
+                   "HyperLogLog string value.\r\n"));
         return REDIS_ERR;
     }
     return REDIS_OK;