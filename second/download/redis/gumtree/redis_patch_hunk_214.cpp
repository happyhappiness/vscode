                 if (reply == (void*)REDIS_REPLY_ERROR) {
                     fprintf(stderr,"Unexpected error reply, exiting...\n");
                     exit(1);
                 }
 
                 freeReplyObject(reply);
-
-                if (c->selectlen) {
-                    size_t j;
-
-                    /* This is the OK from SELECT. Just discard the SELECT
-                     * from the buffer. */
+                /* This is an OK for prefix commands such as auth and select.*/
+                if (c->prefix_pending > 0) {
+                    c->prefix_pending--;
                     c->pending--;
-                    sdsrange(c->obuf,c->selectlen,-1);
-                    /* We also need to fix the pointers to the strings
-                     * we need to randomize. */
-                    for (j = 0; j < c->randlen; j++)
-                        c->randptr[j] -= c->selectlen;
-                    c->selectlen = 0;
-                    continue;
+                    /* Discard prefix commands on first response.*/
+                    if (c->prefixlen > 0) {
+                        size_t j;
+                        sdsrange(c->obuf, c->prefixlen, -1);
+                        /* We also need to fix the pointers to the strings
+                        * we need to randomize. */
+                        for (j = 0; j < c->randlen; j++)
+                            c->randptr[j] -= c->prefixlen;
+                        c->prefixlen = 0;
+                    }
+                    continue;                
                 }
 
                 if (config.requests_finished < config.requests)
                     config.latency[config.requests_finished++] = c->latency;
                 c->pending--;
                 if (c->pending == 0) {
