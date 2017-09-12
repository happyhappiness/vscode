@@ -355,7 +355,8 @@ void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, i
             *score = scoreval;
         }
         if (isnan(*score)) {
-            addReplyError(c,"resulting score is not a number (NaN)");
+            addReplySds(c,
+                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
             zfree(score);
             /* Note that we don't need to check if the zset may be empty and
              * should be removed here, as we can only obtain Nan as score if