         while (apr_isdigit(*pos) || apr_isspace(*pos)) {
             ++pos;
         }
 
         if (*pos != '\0') {
             /* This supplies additional information for the default message. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00590)
                           "Invalid Content-Length %s", lenp);
             return HTTP_BAD_REQUEST;
         }
 
         r->remaining = apr_atoi64(lenp);
     }
