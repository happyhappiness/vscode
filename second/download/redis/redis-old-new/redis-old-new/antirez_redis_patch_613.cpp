@@ -4063,6 +4063,18 @@ void clusterCommand(redisClient *c) {
             addReplyBulkCString(c,ni);
             sdsfree(ni);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"count-failure-reports") &&
+               c->argc == 3)
+    {
+        /* CLUSTER COUNT-FAILURE-REPORTS <NODE ID> */
+        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);
+
+        if (!n) {
+            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
+            return;
+        } else {
+            addReplyLongLong(c,clusterNodeFailureReportsCount(n));
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"failover") &&
                (c->argc == 2 || c->argc == 3))
     {