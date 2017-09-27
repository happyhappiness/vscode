              * behaviour here might break something.
              *
              * So let's make it configurable.
              */
             const char *policy = apr_table_get(r->subprocess_env,
                                                "proxy-interim-response");
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "proxy: HTTP: received interim %d response",
                          r->status);
             if (!policy || !strcasecmp(policy, "RFC")) {
                 ap_send_interim_response(r, 1);
             }
             /* FIXME: refine this to be able to specify per-response-status
