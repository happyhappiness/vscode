              * environment is set.
              */
 
             if (apr_table_get(r->subprocess_env,
                               "AuthDigestEnableQueryStringHack")) {
 
-                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, "Digest: "
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01784)
                               "applying AuthDigestEnableQueryStringHack "
                               "to uri <%s>", resp->raw_request_uri);
 
                d_uri.query = r_uri.query;
             }
         }
 
         if (r->method_number == M_CONNECT) {
             if (!r_uri.hostinfo || strcmp(resp->uri, r_uri.hostinfo)) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "Digest: uri mismatch - <%s> does not match "
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01785)
+                              "uri mismatch - <%s> does not match "
                               "request-uri <%s>", resp->uri, r_uri.hostinfo);
                 return HTTP_BAD_REQUEST;
             }
         }
         else if (
             /* check hostname matches, if present */
