@@ -96,10 +96,8 @@ static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
     if (getLongLongFromObjectOrReply(c,o,&loffset,err) != REDIS_OK)
         return REDIS_ERR;
 
-    /* Limit offset to SIZE_T_MAX or 512MB in bytes */
-    if ((loffset < 0) ||
-        ((unsigned long long)loffset >= (unsigned)SIZE_T_MAX) ||
-        ((unsigned long long)loffset >> 3) >= (512*1024*1024))
+    /* Limit offset to 512MB in bytes */
+    if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
     {
         addReplyError(c,err);
         return REDIS_ERR;