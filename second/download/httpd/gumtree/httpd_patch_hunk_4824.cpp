             }
 
             /* ap_rgetline returns APR_ENOSPC if it fills up the buffer before
              * finding the end-of-line.  This is only going to happen if it
              * exceeds the configured limit for a field size.
              */
-            if (rv == APR_ENOSPC && field) {
-                /* ensure ap_escape_html will terminate correctly */
-                field[len - 1] = '\0';
+            if (rv == APR_ENOSPC) {
+                const char *field_escaped;
+                if (field) {
+                    /* ensure ap_escape_html will terminate correctly */
+                    field[len - 1] = '\0';
+                    field_escaped = ap_escape_html(r->pool, field);
+                }
+                else {
+                    field_escaped = field = "";
+                }
+
                 apr_table_setn(r->notes, "error-notes",
                                apr_psprintf(r->pool,
                                            "Size of a request header field "
                                            "exceeds server limit.<br />\n"
                                            "<pre>\n%.*s\n</pre>\n", 
-                                           field_name_len(field), 
-                                           ap_escape_html(r->pool, field)));
+                                           field_name_len(field_escaped),
+                                           field_escaped));
                 ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00561)
-                              "Request header exceeds LimitRequestFieldSize: "
-                              "%.*s", field_name_len(field), field);
+                              "Request header exceeds LimitRequestFieldSize%s"
+                              "%.*s",
+                              *field ? ": " : "",
+                              field_name_len(field), field);
             }
             return;
         }
 
         if (last_field != NULL) {
             if ((len > 0) && ((*field == '\t') || *field == ' ')) {
