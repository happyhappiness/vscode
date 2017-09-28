     case REDIS_REPLY_ERROR:
         out = sdscatlen(out,r->str,r->len);
         out = sdscatlen(out,"\n",1);
         break;
     case REDIS_REPLY_STATUS:
     case REDIS_REPLY_STRING:
-        out = sdscatlen(out,r->str,r->len);
+        if (r->type == REDIS_REPLY_STATUS && config.eval_ldb) {
+            /* The Lua debugger replies with arrays of simple (status)
+             * strings. We colorize the output for more fun if this
+             * is a debugging session. */
+
+            /* Detect the end of a debugging session. */
+            if (strstr(r->str,"<endsession>") == r->str) {
+                config.enable_ldb_on_eval = 0;
+                config.eval_ldb = 0;
+                config.eval_ldb_end = 1; /* Signal the caller session ended. */
+                config.output = OUTPUT_STANDARD;
+                cliRefreshPrompt();
+            } else {
+                out = sdsCatColorizedLdbReply(out,r->str,r->len);
+            }
+        } else {
+            out = sdscatlen(out,r->str,r->len);
+        }
         break;
     case REDIS_REPLY_INTEGER:
         out = sdscatprintf(out,"%lld",r->integer);
         break;
     case REDIS_REPLY_ARRAY:
         for (i = 0; i < r->elements; i++) {
