 {
     int file_req = (r->main && r->filename);
     int access_status;
 
     /* Ignore embedded %2F's in path for proxy requests */
     if (!r->proxyreq && r->parsed_uri.path) {
-        access_status = ap_unescape_url(r->parsed_uri.path);
+        core_dir_config *d;
+        d = ap_get_module_config(r->per_dir_config, &core_module);
+        if (d->allow_encoded_slashes) {
+            access_status = ap_unescape_url_keep2f(r->parsed_uri.path);
+        }
+        else {
+            access_status = ap_unescape_url(r->parsed_uri.path);
+        }
         if (access_status) {
             if (access_status == HTTP_NOT_FOUND) {
-                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
-                              "found %%2f (encoded '/') in URI "
-                              "(decoded='%s'), returning 404",
-                              r->parsed_uri.path);
+                if (! d->allow_encoded_slashes) {
+                    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                                  "found %%2f (encoded '/') in URI "
+                                  "(decoded='%s'), returning 404",
+                                  r->parsed_uri.path);
+                }
             }
             return access_status;
         }
     }
 
     ap_getparents(r->uri);     /* OK --- shrinking transformations... */
