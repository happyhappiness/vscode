@@ -1323,14 +1323,16 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         clusterNode *node;
         sds ci;
 
-        ci = representClusterNodeFlags(sdsempty(), flags);
-        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d@%d %s",
-            g->nodename,
-            g->ip,
-            ntohs(g->port),
-            ntohs(g->cport),
-            ci);
-        sdsfree(ci);
+        if (server.verbosity == LL_DEBUG) {
+            ci = representClusterNodeFlags(sdsempty(), flags);
+            serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d@%d %s",
+                g->nodename,
+                g->ip,
+                ntohs(g->port),
+                ntohs(g->cport),
+                ci);
+            sdsfree(ci);
+        }
 
         /* Update our state accordingly to the gossip sections */
         node = clusterLookupNode(g->nodename);
@@ -3835,15 +3837,14 @@ static struct redisNodeFlags redisNodeFlagsTable[] = {
 /* Concatenate the comma separated list of node flags to the given SDS
  * string 'ci'. */
 sds representClusterNodeFlags(sds ci, uint16_t flags) {
-    if (flags == 0) {
-        ci = sdscat(ci,"noflags,");
-    } else {
-        int i, size = sizeof(redisNodeFlagsTable)/sizeof(struct redisNodeFlags);
-        for (i = 0; i < size; i++) {
-            struct redisNodeFlags *nodeflag = redisNodeFlagsTable + i;
-            if (flags & nodeflag->flag) ci = sdscat(ci, nodeflag->name);
-        }
-    }
+    size_t orig_len = sdslen(ci);
+    int i, size = sizeof(redisNodeFlagsTable)/sizeof(struct redisNodeFlags);
+    for (i = 0; i < size; i++) {
+        struct redisNodeFlags *nodeflag = redisNodeFlagsTable + i;
+        if (flags & nodeflag->flag) ci = sdscat(ci, nodeflag->name);
+    }
+    /* If no flag was added, add the "noflags" special flag. */
+    if (sdslen(ci) == orig_len) ci = sdscat(ci,"noflags,");
     sdsIncrLen(ci,-1); /* Remove trailing comma. */
     return ci;
 }