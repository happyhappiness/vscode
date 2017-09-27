 
                 apr_brigade_write(bbout, NULL, NULL, data, len);
 
                 status = ap_pass_brigade(r->output_filters, bbout);
                 if (status != APR_SUCCESS) {
                     /* no way to know what type of error occurred */
-                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(01410)
                              "reflector_handler: ap_pass_brigade returned %i",
                                   status);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
 
             }
