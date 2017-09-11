@@ -1211,7 +1211,7 @@ void clientCommand(redisClient *c) {
          * CLIENT LIST format will break. You should always be able to
          * split by space to get the different fields. */
         for (j = 0; j < len; j++) {
-            if (p[j] < '!' || p[j] > '~') { /* ASCI is assumed. */
+            if (p[j] < '!' || p[j] > '~') { /* ASCII is assumed. */
                 addReplyError(c,
                     "Client names cannot contain spaces, "
                     "newlines or special characters.");