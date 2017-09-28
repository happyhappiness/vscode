     querylen = newline-(c->querybuf);
     aux = sdsnewlen(c->querybuf,querylen);
     argv = sdssplitargs(aux,&argc);
     sdsfree(aux);
     if (argv == NULL) {
         addReplyError(c,"Protocol error: unbalanced quotes in request");
-        setProtocolError(c,0);
+        setProtocolError("unbalanced quotes in inline request",c,0);
         return C_ERR;
     }
 
     /* Newline from slaves can be used to refresh the last ACK time.
      * This is useful for a slave to ping back while loading a big
      * RDB file. */
