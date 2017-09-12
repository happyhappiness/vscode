@@ -327,8 +327,7 @@ void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int
             score += *(double*)dictGetEntryVal(de);
 
         if (isnan(score)) {
-            addReplySds(c,
-                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
+            addReplyError(c,"resulting score is not a number (NaN)");
             /* Note that we don't need to check if the zset may be empty and
              * should be removed here, as we can only obtain Nan as score if
              * there was already an element in the sorted set. */