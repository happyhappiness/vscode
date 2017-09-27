              *
              * So let's make it configurable.
              */
             const char *policy = apr_table_get(r->subprocess_env,
                                                "proxy-interim-response");
             ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
-                         "proxy: HTTP: received interim %d response",
-                         r->status);
+                          "HTTP: received interim %d response", r->status);
             if (!policy || !strcasecmp(policy, "RFC")) {
                 ap_send_interim_response(r, 1);
             }
             /* FIXME: refine this to be able to specify per-response-status
              * policies and maybe also add option to bail out with 502
              */
             else if (strcasecmp(policy, "Suppress")) {
-                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
-                             "undefined proxy interim response policy");
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01108)
+                              "undefined proxy interim response policy");
             }
         }
         /* Moved the fixups of Date headers and those affected by
          * ProxyPassReverse/etc from here to ap_proxy_read_headers
          */
 
-        if ((proxy_status == 401) && (conf->error_override)) {
+        if ((proxy_status == 401) && (dconf->error_override)) {
             const char *buf;
             const char *wa = "WWW-Authenticate";
             if ((buf = apr_table_get(r->headers_out, wa))) {
                 apr_table_set(r->err_headers_out, wa, buf);
             } else {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                             "proxy: origin server sent 401 without WWW-Authenticate header");
+                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01109)
+                              "origin server sent 401 without "
+                              "WWW-Authenticate header");
             }
         }
 
         r->sent_bodyct = 1;
         /*
          * Is it an HTTP/0.9 response or did we maybe preread the 1st line of
