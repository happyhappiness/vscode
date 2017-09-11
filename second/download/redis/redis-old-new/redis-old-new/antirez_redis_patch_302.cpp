@@ -3940,6 +3940,11 @@ void clusterCommand(client *c) {
         int slot;
         clusterNode *n;
 
+        if (nodeIsSlave(myself)) {
+            addReplyError(c,"Please use SETSLOT only with masters.");
+            return;
+        }
+
         if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;
 
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {