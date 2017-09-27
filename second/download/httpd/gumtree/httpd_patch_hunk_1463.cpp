              */
             rv = apr_file_write_full(tempsock, data, len, NULL);
 
             if (rv != APR_SUCCESS) {
                 /* silly script stopped reading, soak up remaining message */
                 child_stopped_reading = 1;
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, 
+                              "Error writing request body to script %s", 
+                              r->filename);
+
             }
         }
         apr_brigade_cleanup(bb);
     }
     while (!seen_eos);
 
