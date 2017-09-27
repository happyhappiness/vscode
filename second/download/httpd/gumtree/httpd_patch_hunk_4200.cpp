          * If the script returned a specific status, that's what
          * we'll use - otherwise we assume 200 OK.
          */
         else if (!strcasecmp(w, "Status")) {
             r->status = cgi_status = atoi(l);
             if (!ap_is_HTTP_VALID_RESPONSE(cgi_status))
+                /* Intentional no APLOGNO */
                 ap_log_rerror(SCRIPT_LOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
                               "Invalid status line from script '%s': %.30s",
                               apr_filepath_name_get(r->filename), l);
             else
                 if (APLOGrtrace1(r))
                    ap_log_rerror(SCRIPT_LOG_MARK, APLOG_TRACE1, 0, r,
