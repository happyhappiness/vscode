         return OK;
     }
 
     /* there's an AuthType configured, but no authentication module
      * loaded to support it
      */
-    ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r,
+    ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01796)
                   "AuthType %s configured without corresponding module",
                   ap_auth_type(r));
 
     return HTTP_INTERNAL_SERVER_ERROR;
 }
 
