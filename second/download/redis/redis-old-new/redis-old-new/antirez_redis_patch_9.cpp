@@ -4194,7 +4194,7 @@ void clusterCommand(client *c) {
             }
             if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                 addReplyErrorFormat(c,"I don't know about node %s",
-                    (char*)c->argv[3]->ptr);
+                    (char*)c->argv[4]->ptr);
                 return;
             }
             server.cluster->importing_slots_from[slot] = n;