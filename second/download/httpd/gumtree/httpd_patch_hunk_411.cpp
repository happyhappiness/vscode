         if (d_uri.path) {
             ap_unescape_url(d_uri.path);
         }
         if (d_uri.query) {
             ap_unescape_url(d_uri.query);
         }
+        else if (r_uri.query) {
+            /* MSIE compatibility hack.  MSIE has some RFC issues - doesn't 
+             * include the query string in the uri Authorization component
+             * or when computing the response component.  the second part
+             * works out ok, since we can hash the header and get the same
+             * result.  however, the uri from the request line won't match
+             * the uri Authorization component since the header lacks the 
+             * query string, leaving us incompatable with a (broken) MSIE.
+             * 
+             * the workaround is to fake a query string match if in the proper
+             * environment - BrowserMatch MSIE, for example.  the cool thing
+             * is that if MSIE ever fixes itself the simple match ought to 
+             * work and this code won't be reached anyway, even if the
+             * environment is set.
+             */
+            
+            if (apr_table_get(r->subprocess_env, 
+                              "AuthDigestEnableQueryStringHack")) {
+                d_uri.query = r_uri.query;
+            }
+        }
 
         if (r->method_number == M_CONNECT) {
             if (strcmp(resp->uri, r_uri.hostinfo)) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "Digest: uri mismatch - <%s> does not match "
                               "request-uri <%s>", resp->uri, r_uri.hostinfo);
