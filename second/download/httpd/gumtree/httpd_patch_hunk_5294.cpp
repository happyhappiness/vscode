             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(02442)
                           "error on %s - ap_get_brigade",
                           name);
         }
     } while (rv == APR_SUCCESS);
 
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, rv, r, "wstunnel_transfer complete");
+
     if (APR_STATUS_IS_EAGAIN(rv)) {
         rv = APR_SUCCESS;
     }
+   
     return rv;
 }
 
 /* Search thru the input filters and remove the reqtimeout one */
 static void remove_reqtimeout(ap_filter_t *next)
 {
