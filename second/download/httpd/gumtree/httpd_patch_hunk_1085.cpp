 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
            "ajp_unmarshal_response: status = %d", status);
 
     rc = ajp_msg_get_uint16(msg, &num_headers);
     if (rc == APR_SUCCESS) {
-        r->headers_out = apr_table_make(r->pool, num_headers);
+        apr_table_t *save_table;
+
+        /* First, tuck away all already existing cookies */
+        /*
+         * Could optimize here, but just in case we want to
+         * also save other headers, keep this logic.
+         */
+        save_table = apr_table_make(r->pool, num_headers + 2);
+        apr_table_do(addit_dammit, save_table, r->headers_out,
+                     "Set-Cookie", NULL);
+        r->headers_out = save_table;
     } else {
         r->headers_out = NULL;
         num_headers = 0;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
