@@ -458,7 +458,7 @@ void pfaddCommand(redisClient *c) {
          * exactly. */
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLADD target key must contain a %d bytes string.",
+                "PFADD target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }
@@ -502,7 +502,7 @@ void pfcountCommand(redisClient *c) {
          * exactly. */
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLCOUNT target key must contain a %d bytes string.",
+                "PFCOUNT target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }
@@ -562,7 +562,7 @@ void pfmergeCommand(redisClient *c) {
 
         if (stringObjectLen(o) != REDIS_HLL_SIZE) {
             addReplyErrorFormat(c,
-                "HLLADD target key must contain a %d bytes string.",
+                "PFADD target key must contain a %d bytes string.",
                 REDIS_HLL_SIZE);
             return;
         }