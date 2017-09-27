             r->status_line = "200 OK";
             backend->close += 1;
         }
 
         interim_response = ap_is_HTTP_INFO(r->status);
         if (interim_response) {
+            /* RFC2616 tells us to forward this.
+             *
+             * OTOH, an interim response here may mean the backend
+             * is playing sillybuggers.  The Client didn't ask for
+             * it within the defined HTTP/1.1 mechanisms, and if
+             * it's an extension, it may also be unsupported by us.
+             *
+             * There's also the possibility that changing existing
+             * behaviour here might break something.
+             *
+             * So let's make it configurable.
+             */
+            const char *policy = apr_table_get(r->subprocess_env,
+                                               "proxy-interim-response");
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                          "proxy: HTTP: received interim %d response",
                          r->status);
+            if (!policy || !strcasecmp(policy, "RFC")) {
+                ap_send_interim_response(r, 1);
+            }
+            /* FIXME: refine this to be able to specify per-response-status
+             * policies and maybe also add option to bail out with 502
+             */
+            else if (strcasecmp(policy, "Suppress")) {
+                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
+                             "undefined proxy interim response policy");
+            }
         }
         /* Moved the fixups of Date headers and those affected by
          * ProxyPassReverse/etc from here to ap_proxy_read_headers
          */
 
         if ((r->status == 401) && (conf->error_override)) {
