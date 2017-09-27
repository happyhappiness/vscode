              */
             apr_table_setn(r->notes, "error-notes",
                            "TRACE forbidden by server configuration");
             apr_table_setn(r->notes, "verbose-error-to", "*");
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "proxy: TRACE forbidden by server configuration");
-            return HTTP_FORBIDDEN;
+            return HTTP_METHOD_NOT_ALLOWED;
         }
 
         /* Can't test ap_should_client_block, we aren't ready to send
          * the client a 100 Continue response till the connection has
          * been established
          */
