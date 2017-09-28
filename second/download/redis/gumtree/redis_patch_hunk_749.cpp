         if (schedule) {
             server.rdb_bgsave_scheduled = 1;
             addReplyStatus(c,"Background saving scheduled");
         } else {
             addReplyError(c,
                 "An AOF log rewriting in progress: can't BGSAVE right now. "
-                "Use BGSAVE SCHEDULE in order to schedule a BGSAVE whenver "
+                "Use BGSAVE SCHEDULE in order to schedule a BGSAVE whenever "
                 "possible.");
         }
-    } else if (rdbSaveBackground(server.rdb_filename) == C_OK) {
+    } else if (rdbSaveBackground(server.rdb_filename,NULL) == C_OK) {
         addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);
     }
 }
