         ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, c,
                       "total of %" APR_OFF_T_FMT " bytes in buffer, eos=%d",
                       total, eos);
 
         /* Fail if this exceeds the maximum buffer size. */
         if (total > maxlen) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "request body exceeds maximum size (%" APR_SIZE_T_FMT 
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02018)
+                          "request body exceeds maximum size (%" APR_SIZE_T_FMT
                           ") for SSL buffer", maxlen);
             return HTTP_REQUEST_ENTITY_TOO_LARGE;
         }
 
     } while (!eos);
 
     apr_brigade_destroy(tempb);
 
     /* After consuming all protocol-level input, remove all protocol-level
      * filters.  It should strictly only be necessary to remove filters
-     * at exactly ftype == AP_FTYPE_PROTOCOL, since this filter will 
+     * at exactly ftype == AP_FTYPE_PROTOCOL, since this filter will
      * precede all > AP_FTYPE_PROTOCOL anyway. */
     while (r->proto_input_filters->frec->ftype < AP_FTYPE_CONNECTION) {
         ap_remove_input_filter(r->proto_input_filters);
     }
 
     /* Insert the filter which will supply the buffered content. */
