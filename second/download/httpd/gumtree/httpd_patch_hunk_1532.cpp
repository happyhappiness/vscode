      * cache_save_filter_handle / cache_out_filter_handle to be used by
      * main requests and
      * cache_save_subreq_filter_handle / cache_out_subreq_filter_handle
      * to be run by subrequest
      */
     /*
+     * CACHE is placed into the filter chain at an admin specified location,
+     * and when the cache_handler is run, the CACHE filter is swapped with
+     * the CACHE_OUT filter, or CACHE_SAVE filter as appropriate. This has
+     * the effect of offering optional fine control of where the cache is
+     * inserted into the filter chain.
+     */
+    cache_filter_handle =
+        ap_register_output_filter("CACHE",
+                                  cache_filter,
+                                  NULL,
+                                  AP_FTYPE_RESOURCE);
+    /*
      * CACHE_SAVE must go into the filter chain after a possible DEFLATE
      * filter to ensure that the compressed content is stored.
      * Incrementing filter type by 1 ensures his happens.
      */
     cache_save_filter_handle =
         ap_register_output_filter("CACHE_SAVE",
