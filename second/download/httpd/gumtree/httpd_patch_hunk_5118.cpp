             r->status = cgi_status = atoi(l);
             if (!ap_is_HTTP_VALID_RESPONSE(cgi_status))
                 ap_log_rerror(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                               "Invalid status line from script '%s': %.30s",
                               apr_filepath_name_get(r->filename), l);
             else
-                ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE1, 0, r,
-                              "Status line from script '%s': %.30s",
-                              apr_filepath_name_get(r->filename), l);
+                if (APLOGrtrace1(r))
+                   ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE1, 0, r,
+                                 "Status line from script '%s': %.30s",
+                                 apr_filepath_name_get(r->filename), l);
             r->status_line = apr_pstrdup(r->pool, l);
         }
         else if (!strcasecmp(w, "Location")) {
             apr_table_set(r->headers_out, w, l);
         }
         else if (!strcasecmp(w, "Content-Length")) {
