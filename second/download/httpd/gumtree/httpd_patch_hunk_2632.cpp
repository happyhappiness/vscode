     }
 
     /* get the destination URI */
     dest = apr_table_get(r->headers_in, "Destination");
     if (dest == NULL) {
         /* This supplies additional information for the default message. */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00620)
                       "The request is missing a Destination header.");
         return HTTP_BAD_REQUEST;
     }
 
     lookup = dav_lookup_uri(dest, r, 0 /* must_be_absolute */);
     if (lookup.rnew == NULL) {
         if (lookup.err.status == HTTP_BAD_REQUEST) {
             /* This supplies additional information for the default message. */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00621)
                           "%s", lookup.err.desc);
             return HTTP_BAD_REQUEST;
         }
         else if (lookup.err.status == HTTP_BAD_GATEWAY) {
             /* ### Bindings protocol draft 02 says to return 507
              * ### (Cross Server Binding Forbidden); Apache already defines 507
