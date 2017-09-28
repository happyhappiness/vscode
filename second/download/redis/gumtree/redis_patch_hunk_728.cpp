     newline = strchr(c->querybuf,'\n');
 
     /* Nothing to do without a \r\n */
     if (newline == NULL) {
         if (sdslen(c->querybuf) > PROTO_INLINE_MAX_SIZE) {
             addReplyError(c,"Protocol error: too big inline request");
-            setProtocolError(c,0);
+            setProtocolError("too big inline request",c,0);
         }
         return C_ERR;
     }
 
     /* Handle the \r\n case. */
     if (newline && newline != c->querybuf && *(newline-1) == '\r')
