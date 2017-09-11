@@ -4071,7 +4071,7 @@ void clusterCommand(redisClient *c) {
         }
 
         /* Can't replicate a slave. */
-        if (n->slaveof != NULL) {
+        if (nodeIsSlave(n)) {
             addReplyError(c,"I can only replicate a master, not a slave.");
             return;
         }