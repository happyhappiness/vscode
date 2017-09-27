 
     ap_log_rerror(APLOG_MARK, APLOG_TRACE2, rv, r, "wstunnel_transfer complete");
 
     if (APR_STATUS_IS_EAGAIN(rv)) {
         rv = APR_SUCCESS;
     }
-   
+
     return rv;
 }
 
 /*
  * process the request and write the response.
  */
