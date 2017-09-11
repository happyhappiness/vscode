@@ -2314,6 +2314,14 @@ void clusterCommand(redisClient *c) {
             (unsigned long)sdslen(info)));
         addReplySds(c,info);
         addReply(c,shared.crlf);
+    } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
+        int retval = clusterSaveConfig();
+
+        if (retval == 0)
+            addReply(c,shared.ok);
+        else
+            addReplyErrorFormat(c,"error saving the cluster node config: %s",
+                strerror(errno));
     } else if (!strcasecmp(c->argv[1]->ptr,"keyslot") && c->argc == 3) {
         /* CLUSTER KEYSLOT <key> */
         sds key = c->argv[2]->ptr;