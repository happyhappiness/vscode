                                   cache_filter,
                                   NULL,
                                   AP_FTYPE_RESOURCE);
     /*
      * CACHE_SAVE must go into the filter chain after a possible DEFLATE
      * filter to ensure that the compressed content is stored.
-     * Incrementing filter type by 1 ensures his happens.
+     * Incrementing filter type by 1 ensures this happens.
      */
     cache_save_filter_handle =
         ap_register_output_filter("CACHE_SAVE",
                                   cache_save_filter,
                                   NULL,
                                   AP_FTYPE_CONTENT_SET+1);
