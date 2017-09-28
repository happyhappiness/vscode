     redisCommandProc *prevcmd = c->cmd ? c->cmd->proc : NULL;
 
     freeClientArgv(c);
     c->reqtype = 0;
     c->multibulklen = 0;
     c->bulklen = -1;
+
     /* We clear the ASKING flag as well if we are not inside a MULTI, and
      * if what we just executed is not the ASKING command itself. */
-    if (!(c->flags & REDIS_MULTI) && prevcmd != askingCommand)
-        c->flags &= (~REDIS_ASKING);
+    if (!(c->flags & CLIENT_MULTI) && prevcmd != askingCommand)
+        c->flags &= ~CLIENT_ASKING;
+
+    /* Remove the CLIENT_REPLY_SKIP flag if any so that the reply
+     * to the next command will be sent, but set the flag if the command
+     * we just processed was "CLIENT REPLY SKIP". */
+    c->flags &= ~CLIENT_REPLY_SKIP;
+    if (c->flags & CLIENT_REPLY_SKIP_NEXT) {
+        c->flags |= CLIENT_REPLY_SKIP;
+        c->flags &= ~CLIENT_REPLY_SKIP_NEXT;
+    }
 }
 
-int processInlineBuffer(redisClient *c) {
+int processInlineBuffer(client *c) {
     char *newline;
     int argc, j;
     sds *argv, aux;
     size_t querylen;
 
     /* Search for end of line */
     newline = strchr(c->querybuf,'\n');
 
     /* Nothing to do without a \r\n */
     if (newline == NULL) {
-        if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+        if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
             addReplyError(c,"Protocol error: too big inline request");
             setProtocolError(c,0);
         }
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Handle the \r\n case. */
     if (newline && newline != c->querybuf && *(newline-1) == '\r')
         newline--;
 
