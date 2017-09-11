@@ -293,6 +293,7 @@ void debugCommand(client *c) {
         serverLog(LL_WARNING,"DB reloaded by DEBUG RELOAD");
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
+        if (server.aof_state == AOF_ON) flushAppendOnlyFile(1);
         emptyDb(-1,EMPTYDB_NO_FLAGS,NULL);
         if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
             addReply(c,shared.err);