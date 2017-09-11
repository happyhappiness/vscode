@@ -3791,7 +3791,7 @@ void restoreCommand(redisClient *c) {
 
     /* Make sure this key does not already exist here... */
     if (!replace && lookupKeyWrite(c->db,c->argv[1]) != NULL) {
-        addReplyError(c,"Target key name is busy.");
+        addReply(c,shared.busykeyerr);
         return;
     }
 