                     *searchptr = ']';
             }
 
             filename = strrchr(ctx->buffer, ' ');
             if (filename == NULL) {
                 /* Line is broken.  Ignore it. */
-                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
-                             "proxy_ftp: could not parse line %s", ctx->buffer);
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01034)
+                              "proxy_ftp: could not parse line %s",
+                              ctx->buffer);
                 /* erase buffer for next time around */
                 ctx->buffer[0] = 0;
                 continue;  /* while state is BODY */
             }
             *(filename++) = '\0';
 
