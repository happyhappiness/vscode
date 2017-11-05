static void register_hooks(apr_pool_t *p)
{
    /* cache initializer */
    /* cache handler */
    ap_hook_quick_handler(cache_url_handler, NULL, NULL, APR_HOOK_FIRST);
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
    cache_out_filter_handle = 
        ap_register_output_filter("CACHE_OUT", 
                                  cache_out_filter, 
                                  NULL,
                                  AP_FTYPE_CONTENT_SET-1);
    cache_conditional_filter_handle =
        ap_register_output_filter("CACHE_CONDITIONAL", 
                                  cache_conditional_filter, 
                                  NULL,
                                  AP_FTYPE_CONTENT_SET);
    ap_hook_post_config(cache_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
}