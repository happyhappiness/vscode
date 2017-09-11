@@ -248,7 +248,17 @@ void sortCommand(redisClient *c) {
             sortby = c->argv[j+1];
             /* If the BY pattern does not contain '*', i.e. it is constant,
              * we don't need to sort nor to lookup the weight keys. */
-            if (strchr(c->argv[j+1]->ptr,'*') == NULL) dontsort = 1;
+            if (strchr(c->argv[j+1]->ptr,'*') == NULL) {
+                dontsort = 1;
+            } else {
+                /* If BY is specified with a real patter, we can't accept
+                 * it in cluster mode. */
+                if (server.cluster_enabled) {
+                    addReplyError(c,"BY option of SORT denied in Cluster mode.");
+                    syntax_error++;
+                    break;
+                }
+            }
             j++;
         } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
             if (server.cluster_enabled) {