 
             token = ap_get_token(r->pool, &tmp, 0);
             while (token && *token) {
                 /* stolen from mod_negotiation: */
                 if (strcmp(token, "identity") && strcmp(token, "7bit") &&
                     strcmp(token, "8bit") && strcmp(token, "binary")) {
-
+                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
+                                  "Not compressing (content-encoding already "
+                                  " set: %s)", token);
                     ap_remove_output_filter(f);
                     return ap_pass_brigade(f->next, bb);
                 }
 
                 /* Otherwise, skip token */
                 if (*tmp) {
