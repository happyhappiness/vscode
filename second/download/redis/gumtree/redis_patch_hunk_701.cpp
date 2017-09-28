                 addReplyErrorFormat(c,
                     "I'm already the owner of hash slot %u",slot);
                 return;
             }
             if ((n = clusterLookupNode(c->argv[4]->ptr)) == NULL) {
                 addReplyErrorFormat(c,"I don't know about node %s",
-                    (char*)c->argv[4]->ptr);
+                    (char*)c->argv[3]->ptr);
                 return;
             }
             server.cluster->importing_slots_from[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"stable") && c->argc == 4) {
             /* CLUSTER SETSLOT <SLOT> STABLE */
             server.cluster->importing_slots_from[slot] = NULL;
