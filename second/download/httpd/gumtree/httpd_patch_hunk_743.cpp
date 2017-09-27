 
                 get_entry(neg->pool, &accept_info, body);
                 set_mime_fields(&mime_info, &accept_info);
                 has_content = 1;
             }
             else if (!strncmp(buffer, "content-length:", 15)) {
-                mime_info.bytes = apr_atoi64((char *)body);
+                char *errp;
+                apr_off_t number;
+
+                if (apr_strtoff(&number, body, &errp, 10)
+                    || *errp || number < 0) {
+                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                                  "Parse error in type map, Content-Length: "
+                                  "'%s' in %s is invalid.",
+                                  body, r->filename);
+                    break;
+                }
+                mime_info.bytes = number;
                 has_content = 1;
             }
             else if (!strncmp(buffer, "content-language:", 17)) {
                 mime_info.content_languages = do_languages_line(neg->pool,
                                                                 &body);
                 has_content = 1;
