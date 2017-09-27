                             /* suck in all the rest */
                             if (status != OK) {
                                 apr_bucket *tmp_b;
                                 apr_brigade_cleanup(ob);
                                 tmp_b = apr_bucket_eos_create(c->bucket_alloc);
                                 APR_BRIGADE_INSERT_TAIL(ob, tmp_b);
+
+                                *has_responded = 1;
                                 r->status = status;
-                                ap_pass_brigade(r->output_filters, ob);
-                                if (status == HTTP_NOT_MODIFIED) {
+                                rv = ap_pass_brigade(r->output_filters, ob);
+                                if (rv != APR_SUCCESS) {
+                                    *err = "passing headers brigade to output filters";
+                                }
+                                else if (status == HTTP_NOT_MODIFIED) {
                                     /* The 304 response MUST NOT contain
                                      * a message-body, ignore it. */
                                     ignore_body = 1;
                                 }
                                 else {
                                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
