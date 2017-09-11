@@ -263,6 +263,8 @@ static client createClient(char *cmd, size_t len) {
             fprintf(stderr,"%s: %s\n",config.hostsocket,c->context->errstr);
         exit(1);
     }
+    /* Suppress hiredis cleanup of unused buffers for max speed. */
+    c->context->reader->maxbuf = 0;
     /* Queue N requests accordingly to the pipeline size. */
     c->obuf = sdsempty();
     for (j = 0; j < config.pipeline; j++)