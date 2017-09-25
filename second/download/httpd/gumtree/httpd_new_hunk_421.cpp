    /* cache filters 
     * XXX The cache filters need to run right after the handlers and before
     * any other filters. Consider creating AP_FTYPE_CACHE for this purpose.
     * Make them AP_FTYPE_CONTENT for now.
     * XXX ianhH:they should run AFTER all the other content filters.
     */
    cache_save_filter_handle = 
        ap_register_output_filter("CACHE_SAVE", 
                                  cache_save_filter, 
                                  NULL,
                                  AP_FTYPE_CONTENT_SET-1);
    /* CACHE_OUT must go into the filter chain before SUBREQ_CORE to
     * handle subrequsts. Decrementing filter type by 1 ensures this 
     * happens.
     */
