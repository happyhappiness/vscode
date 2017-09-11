@@ -1219,18 +1219,23 @@ void clusterCommand(redisClient *c) {
             return;
         }
         slot = (unsigned int) aux;
-        if (server.cluster.slots[slot] != server.cluster.myself) {
-            addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
-            return;
-        }
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
+            if (server.cluster.slots[slot] != server.cluster.myself) {
+                addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
+                return;
+            }
             if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                 addReplyErrorFormat(c,"I don't know about node %s",
                     (char*)c->argv[4]->ptr);
                 return;
             }
             server.cluster.migrating_slots_to[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
+            if (server.cluster.slots[slot] == server.cluster.myself) {
+                addReplyErrorFormat(c,
+                    "I'm already the owner of hash slot %u",slot);
+                return;
+            }
             if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                 addReplyErrorFormat(c,"I don't know about node %s",
                     (char*)c->argv[3]->ptr);