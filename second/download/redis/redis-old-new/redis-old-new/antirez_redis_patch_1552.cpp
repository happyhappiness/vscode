@@ -281,6 +281,12 @@ void debugCommand(redisClient *c) {
             d = sdscatprintf(d, "%02x",digest[j]);
         addReplyStatus(c,d);
         sdsfree(d);
+    } else if (!strcasecmp(c->argv[1]->ptr,"sleep") && c->argc == 3) {
+        double dtime = strtod(c->argv[2]->ptr,NULL);
+        long long utime = dtime*1000000;
+
+        usleep(utime);
+        addReply(c,shared.ok);
     } else {
         addReplyError(c,
             "Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]");