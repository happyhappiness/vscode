             "</a></em>.<p>\n"
             "Reason: <strong>", ap_escape_html(r->pool, message),
             "</strong></p>",
             NULL));
 
     /* Allow "error-notes" string to be printed by ap_send_error_response() */
-    apr_table_setn(r->notes, "verbose-error-to", apr_pstrdup(r->pool, "*"));
+    apr_table_setn(r->notes, "verbose-error-to", "*");
 
     r->status_line = apr_psprintf(r->pool, "%3.3u Proxy Error", statuscode);
     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00898) "%s returned by %s", message,
                   r->uri);
     return statuscode;
 }
