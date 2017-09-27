      */
     cache_out_filter_handle = 
         ap_register_output_filter("CACHE_OUT", 
                                   cache_out_filter, 
                                   NULL,
                                   AP_FTYPE_CONTENT_SET-1);
-    cache_conditional_filter_handle =
-        ap_register_output_filter("CACHE_CONDITIONAL", 
-                                  cache_conditional_filter, 
-                                  NULL,
-                                  AP_FTYPE_CONTENT_SET);
     ap_hook_post_config(cache_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
 }
 
 module AP_MODULE_DECLARE_DATA cache_module =
 {
     STANDARD20_MODULE_STUFF,
