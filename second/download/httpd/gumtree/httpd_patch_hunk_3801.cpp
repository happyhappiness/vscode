                                   input_brigade, (old_cl_val != NULL)
                                               || (old_te_val != NULL)
                                               || (bytes_read > 0));
         break;
     default:
         /* shouldn't be possible */
-        rv = HTTP_INTERNAL_SERVER_ERROR ;
+        rv = HTTP_INTERNAL_SERVER_ERROR;
         break;
     }
 
     if (rv != OK) {
         /* apr_status_t value has been logged in lower level method */
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01097)
