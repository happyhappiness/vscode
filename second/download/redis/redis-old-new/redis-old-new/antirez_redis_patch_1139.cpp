@@ -974,8 +974,8 @@ void configGetCommand(redisClient *c) {
         int j;
 
         for (j = 0; j < server.saveparamslen; j++) {
-            buf = sdscatprintf(buf,"%ld %d",
-                    server.saveparams[j].seconds,
+            buf = sdscatprintf(buf,"%jd %d",
+                    (intmax_t)server.saveparams[j].seconds,
                     server.saveparams[j].changes);
             if (j != server.saveparamslen-1)
                 buf = sdscatlen(buf," ",1);