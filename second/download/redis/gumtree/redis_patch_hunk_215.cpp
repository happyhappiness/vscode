     c->context->reader->maxbuf = 0;
 
     /* Build the request buffer:
      * Queue N requests accordingly to the pipeline size, or simply clone
      * the example client buffer. */
     c->obuf = sdsempty();
-
+    /* Prefix the request buffer with AUTH and/or SELECT commands, if applicable.
+     * These commands are discarded after the first response, so if the client is
+     * reused the commands will not be used again. */
+    c->prefix_pending = 0;
     if (config.auth) {
         char *buf = NULL;
         int len = redisFormatCommand(&buf, "AUTH %s", config.auth);
         c->obuf = sdscatlen(c->obuf, buf, len);
         free(buf);
+        c->prefix_pending++;
     }
 
     /* If a DB number different than zero is selected, prefix our request
      * buffer with the SELECT command, that will be discarded the first
      * time the replies are received, so if the client is reused the
      * SELECT command will not be used again. */
     if (config.dbnum != 0) {
         c->obuf = sdscatprintf(c->obuf,"*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
             (int)sdslen(config.dbnumstr),config.dbnumstr);
-        c->selectlen = sdslen(c->obuf);
-    } else {
-        c->selectlen = 0;
+        c->prefix_pending++;
     }
-
+    c->prefixlen = sdslen(c->obuf);
     /* Append the request itself. */
     if (from) {
         c->obuf = sdscatlen(c->obuf,
-            from->obuf+from->selectlen,
-            sdslen(from->obuf)-from->selectlen);
+            from->obuf+from->prefixlen,
+            sdslen(from->obuf)-from->prefixlen);
     } else {
         for (j = 0; j < config.pipeline; j++)
             c->obuf = sdscatlen(c->obuf,cmd,len);
     }
 
     c->written = 0;
-    c->pending = config.pipeline;
+    c->pending = config.pipeline+c->prefix_pending;
     c->randptr = NULL;
     c->randlen = 0;
-    if (c->selectlen) c->pending++;
 
     /* Find substrings in the output buffer that need to be randomized. */
     if (config.randomkeys) {
         if (from) {
             c->randlen = from->randlen;
             c->randfree = 0;
             c->randptr = zmalloc(sizeof(char*)*c->randlen);
             /* copy the offsets. */
             for (j = 0; j < (int)c->randlen; j++) {
                 c->randptr[j] = c->obuf + (from->randptr[j]-from->obuf);
                 /* Adjust for the different select prefix length. */
-                c->randptr[j] += c->selectlen - from->selectlen;
+                c->randptr[j] += c->prefixlen - from->prefixlen;
             }
         } else {
             char *p = c->obuf;
 
             c->randlen = 0;
             c->randfree = RANDPTR_INITIAL_SIZE;
