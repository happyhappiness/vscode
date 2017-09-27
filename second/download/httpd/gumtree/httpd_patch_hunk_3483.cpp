                 if (r->server->limit_req_fields
                     && (++fields_read > r->server->limit_req_fields)) {
                     r->status = HTTP_BAD_REQUEST;
                     apr_table_setn(r->notes, "error-notes",
                                    "The number of request header fields "
                                    "exceeds this server's limit.");
+                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00563)
+                                  "Number of request headers exceeds "
+                                  "LimitRequestFields");
                     return;
                 }
 
                 if (!(value = strchr(last_field, ':'))) { /* Find ':' or    */
                     r->status = HTTP_BAD_REQUEST;      /* abort bad request */
                     apr_table_setn(r->notes, "error-notes",
-                                   apr_pstrcat(r->pool,
+                                   apr_psprintf(r->pool,
                                                "Request header field is "
                                                "missing ':' separator.<br />\n"
-                                               "<pre>\n",
+                                               "<pre>\n%.*s</pre>\n", 
+                                               (int)LOG_NAME_MAX_LEN,
                                                ap_escape_html(r->pool,
-                                                              last_field),
-                                               "</pre>\n", NULL));
+                                                              last_field)));
+                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00564)
+                                  "Request header field is missing ':' "
+                                  "separator: %.*s", (int)LOG_NAME_MAX_LEN,
+                                  last_field);
                     return;
                 }
 
                 tmp_field = value - 1; /* last character of field-name */
 
                 *value++ = '\0'; /* NUL-terminate at colon */
