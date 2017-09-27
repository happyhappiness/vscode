                                   "Request header field is missing ':' "
                                   "separator: %.*s", (int)LOG_NAME_MAX_LEN,
                                   last_field);
                     return;
                 }
 
-                /* last character of field-name */
-                tmp_field = value - (value > last_field ? 1 : 0);
+                if (value == last_field) {
+                    r->status = HTTP_BAD_REQUEST;
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03453)
+                                  "Request header field name was empty");
+                    return;
+                }
 
                 *value++ = '\0'; /* NUL-terminate at colon */
 
                 if (strpbrk(last_field, "\t\n\v\f\r ")) {
                     r->status = HTTP_BAD_REQUEST;
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03452)
