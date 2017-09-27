     
     if (name[0] == ':') {
         /* pseudo header, see ch. 8.1.2.3, always should come first */
         if (!apr_is_empty_table(req->headers)) {
             ap_log_perror(APLOG_MARK, APLOG_ERR, 0, pool,
                           APLOGNO(02917) 
-                          "h2_request(%d): pseudo header after request start",
-                          req->id);
+                          "h2_request: pseudo header after request start");
             return APR_EGENERAL;
         }
         
         if (H2_HEADER_METHOD_LEN == nlen
             && !strncmp(H2_HEADER_METHOD, name, nlen)) {
             req->method = apr_pstrndup(pool, value, vlen);
