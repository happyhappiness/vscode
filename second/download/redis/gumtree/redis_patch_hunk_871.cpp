 
 void saveCommand(client *c) {
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
     }
-    if (rdbSave(server.rdb_filename,NULL) == C_OK) {
+    rdbSaveInfo rsi, *rsiptr;
+    rsiptr = rdbPopulateSaveInfo(&rsi);
+    if (rdbSave(server.rdb_filename,rsiptr) == C_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
     }
 }
 
