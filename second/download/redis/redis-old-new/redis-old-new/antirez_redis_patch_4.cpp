@@ -3602,8 +3602,10 @@ int clusterDelNodeSlots(clusterNode *node) {
     int deleted = 0, j;
 
     for (j = 0; j < CLUSTER_SLOTS; j++) {
-        if (clusterNodeGetSlotBit(node,j)) clusterDelSlot(j);
-        deleted++;
+        if (clusterNodeGetSlotBit(node,j)) {
+            clusterDelSlot(j);
+            deleted++;
+        }
     }
     return deleted;
 }
@@ -4195,7 +4197,7 @@ void clusterCommand(client *c) {
             }
             if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                 addReplyErrorFormat(c,"I don't know about node %s",
-                    (char*)c->argv[3]->ptr);
+                    (char*)c->argv[4]->ptr);
                 return;
             }
             server.cluster->importing_slots_from[slot] = n;