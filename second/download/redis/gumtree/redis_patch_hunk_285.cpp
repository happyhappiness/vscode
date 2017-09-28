         } else if (!strcasecmp(c->argv[j]->ptr,"limit") && leftargs >= 2) {
             if ((getLongFromObjectOrReply(c, c->argv[j+1], &limit_start, NULL)
                  != REDIS_OK) ||
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
             storekey = c->argv[j+1];
             j++;
         } else if (!strcasecmp(c->argv[j]->ptr,"by") && leftargs >= 1) {
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
     /* When sorting a set with no sort specified, we must sort the output
      * so the result is consistent across scripting and replication.
      *
      * The other types (list, sorted set) will retain their native order
      * even if no sort order is requested, so they remain stable across
      * scripting and replication. */
