      */
     cache_remove_url_filter_handle =
         ap_register_output_filter("CACHE_REMOVE_URL",
                                   cache_remove_url_filter,
                                   NULL,
                                   AP_FTYPE_PROTOCOL);
+    cache_invalidate_filter_handle =
+        ap_register_output_filter("CACHE_INVALIDATE",
+                                  cache_invalidate_filter,
+                                  NULL,
+                                  AP_FTYPE_PROTOCOL);
     ap_hook_post_config(cache_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
 }
 
 AP_DECLARE_MODULE(cache) =
 {
     STANDARD20_MODULE_STUFF,
