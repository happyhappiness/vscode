     * cache_save_filter_handle / cache_out_filter_handle to be used by
     * main requests and
     * cache_save_subreq_filter_handle / cache_out_subreq_filter_handle
     * to be run by subrequest
     */
    /*
     * CACHE_SAVE must go into the filter chain after a possible DEFLATE
     * filter to ensure that the compressed content is stored.
     * Incrementing filter type by 1 ensures his happens.
     */
    cache_save_filter_handle =
        ap_register_output_filter("CACHE_SAVE",
