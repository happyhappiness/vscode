@@ -1396,6 +1396,13 @@ void pfdebugCommand(redisClient *c) {
         decoded = sdstrim(decoded," ");
         addReplyBulkCBuffer(c,decoded,sdslen(decoded));
         sdsfree(decoded);
+    }
+    /* PFDEBUG ENCODING <key> */
+    else if (!strcasecmp(cmd,"encoding")) {
+        char *encodingstr[2] = {"dense","sparse"};
+        if (c->argc != 3) goto arityerr;
+
+        addReplyStatus(c,encodingstr[hdr->encoding]);
     } else {
         addReplyErrorFormat(c,"Unknown PFDEBUG subcommand '%s'", cmd);
     }