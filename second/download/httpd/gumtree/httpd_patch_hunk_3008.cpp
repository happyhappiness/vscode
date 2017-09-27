                                                     readbuflen,
                                                     c->bucket_alloc);
 
                     APR_BRIGADE_INSERT_TAIL(ob, b);
 
                     if (! seen_end_of_headers) {
-                        int st = handle_headers(r, &header_state, readbuf, ob);
+                        int st = handle_headers(r, &header_state, readbuf);
 
                         if (st == 1) {
+                            int status;
                             seen_end_of_headers = 1;
 
-                            rv = ap_pass_brigade(r->output_filters, ob);
-                            if (rv != APR_SUCCESS) {
+                            status = ap_scan_script_header_err_brigade_ex(r, ob,
+                                NULL, APLOG_MODULE_INDEX);
+                            /* suck in all the rest */
+                            if (status != OK) {
+                                apr_bucket *tmp_b;
+                                apr_brigade_cleanup(ob);
+                                tmp_b = apr_bucket_eos_create(c->bucket_alloc);
+                                APR_BRIGADE_INSERT_TAIL(ob, tmp_b);
+                                ap_pass_brigade(r->output_filters, ob);
+                                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
+                                              "Error parsing script headers");
+                                r->status = status;
+                                rv = APR_EINVAL;
                                 break;
                             }
 
+                            if (conf->error_override &&
+                                ap_is_HTTP_ERROR(r->status)) {
+                                /*
+                                 * set script_error_status to discard
+                                 * everything after the headers
+                                 */
+                                script_error_status = r->status;
+                                /*
+                                 * prevent ap_die() from treating this as a
+                                 * recursive error, initially:
+                                 */
+                                r->status = HTTP_OK;
+                            }
+
+                            if (script_error_status == HTTP_OK) {
+                                rv = ap_pass_brigade(r->output_filters, ob);
+                                if (rv != APR_SUCCESS) {
+                                    break;
+                                }
+                            }
                             apr_brigade_cleanup(ob);
 
                             apr_pool_clear(setaside_pool);
                         }
-                        else if (st == -1) {
-                            rv = APR_EINVAL;
-                            break;
-                        }
                         else {
                             /* We're still looking for the end of the
                              * headers, so this part of the data will need
                              * to persist. */
                             apr_bucket_setaside(b, setaside_pool);
                         }
