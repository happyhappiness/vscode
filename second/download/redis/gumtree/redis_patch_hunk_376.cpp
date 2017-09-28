         /* SETSLOT 10 IMPORTING <node ID> */
         /* SETSLOT 10 STABLE */
         /* SETSLOT 10 NODE <node ID> */
         int slot;
         clusterNode *n;
 
+        if (nodeIsSlave(myself)) {
+            addReplyError(c,"Please use SETSLOT only with masters.");
+            return;
+        }
+
         if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;
 
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
             if (server.cluster->slots[slot] != myself) {
                 addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
                 return;
