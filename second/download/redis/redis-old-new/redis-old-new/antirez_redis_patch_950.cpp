@@ -194,6 +194,7 @@ void sortCommand(redisClient *c) {
     int j, dontsort = 0, vectorlen;
     int getop = 0; /* GET operation counter */
     int int_convertion_error = 0;
+    int syntax_error = 0;
     robj *sortval, *sortby = NULL, *storekey = NULL;
     redisSortObject *vector; /* Resulting vector to sort */
 
@@ -236,9 +237,8 @@ void sortCommand(redisClient *c) {
                 (getLongFromObjectOrReply(c, c->argv[j+2], &limit_count, NULL)
                  != REDIS_OK))
             {
-                decrRefCount(sortval);
-                listRelease(operations);
-                return;
+                syntax_error++;
+                break;
             }
             j+=2;
         } else if (!strcasecmp(c->argv[j]->ptr,"store") && leftargs >= 1) {
@@ -251,19 +251,30 @@ void sortCommand(redisClient *c) {
             if (strchr(c->argv[j+1]->ptr,'*') == NULL) dontsort = 1;
             j++;
         } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
+            if (server.cluster_enabled) {
+                addReplyError(c,"GET option of SORT denied in Cluster mode.");
+                syntax_error++;
+                break;
+            }
             listAddNodeTail(operations,createSortOperation(
                 REDIS_SORT_GET,c->argv[j+1]));
             getop++;
             j++;
         } else {
-            decrRefCount(sortval);
-            listRelease(operations);
             addReply(c,shared.syntaxerr);
-            return;
+            syntax_error++;
+            break;
         }
         j++;
     }
 
+    /* Handle syntax errors set during options parsing. */
+    if (syntax_error) {
+        decrRefCount(sortval);
+        listRelease(operations);
+        return;
+    }
+
     /* For the STORE option, or when SORT is called from a Lua script,
      * we want to force a specific ordering even when no explicit ordering
      * was asked (SORT BY nosort). This guarantees that replication / AOF