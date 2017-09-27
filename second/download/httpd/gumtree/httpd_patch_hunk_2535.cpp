                                   NULL,
                                   AP_FTYPE_CONTENT_SET-1);
     /*
      * CACHE_OUT must go into the filter chain after a possible DEFLATE
      * filter to ensure that already compressed cache objects do not
      * get compressed again. Incrementing filter type by 1 ensures
-     * his happens.
+     * this happens.
      */
     cache_out_filter_handle =
         ap_register_output_filter("CACHE_OUT",
                                   cache_out_filter,
                                   NULL,
                                   AP_FTYPE_CONTENT_SET+1);
