static void register_hooks(apr_pool_t *p)
{
    /* cache initializer */
    /* cache quick handler */
    ap_hook_quick_handler(cache_quick_handler, NULL, NULL, APR_HOOK_FIRST);
    /* cache handler */
    ap_hook_handler(cache_handler, NULL, NULL, APR_HOOK_REALLY_FIRST);
    /* cache status */
    cache_hook_cache_status(cache_status, NULL, NULL, APR_HOOK_MIDDLE);
    /* cache error handler */
    ap_hook_insert_error_filter(cache_insert_error_filter, NULL, NULL, APR_HOOK_MIDDLE);
    /* cache filters
     * XXX The cache filters need to run right after the handlers and before
     * any other filters. Consider creating AP_FTYPE_CACHE for this purpose.
     *
     * Depending on the type of request (subrequest / main request) they
     * need to be run before AP_FTYPE_CONTENT_SET / after AP_FTYPE_CONTENT_SET
     * filters. Thus create two filter handles for each type:
     * cache_save_filter_handle / cache_out_filter_handle to be used by
     * main requests and
     * cache_save_subreq_filter_handle / cache_out_subreq_filter_handle
     * to be run by subrequest
     */
    /*
     * CACHE is placed into the filter chain at an admin specified location,
     * and when the cache_handler is run, the CACHE filter is swapped with
     * the CACHE_OUT filter, or CACHE_SAVE filter as appropriate. This has
     * the effect of offering optional fine control of where the cache is
     * inserted into the filter chain.
     */
    cache_filter_handle =
        ap_register_output_filter("CACHE",
                                  cache_filter,
                                  NULL,
                                  AP_FTYPE_RESOURCE);
    /*
     * CACHE_SAVE must go into the filter chain after a possible DEFLATE
     * filter to ensure that the compressed content is stored.
     * Incrementing filter type by 1 ensures this happens.
     */
    cache_save_filter_handle =
        ap_register_output_filter("CACHE_SAVE",
                                  cache_save_filter,
                                  NULL,
                                  AP_FTYPE_CONTENT_SET+1);
    /*
     * CACHE_SAVE_SUBREQ must go into the filter chain before SUBREQ_CORE to
     * handle subrequsts. Decrementing filter type by 1 ensures this
     * happens.
     */
    cache_save_subreq_filter_handle =
        ap_register_output_filter("CACHE_SAVE_SUBREQ",
                                  cache_save_filter,
                                  NULL,
                                  AP_FTYPE_CONTENT_SET-1);
    /*
     * CACHE_OUT must go into the filter chain after a possible DEFLATE
     * filter to ensure that already compressed cache objects do not
     * get compressed again. Incrementing filter type by 1 ensures
     * this happens.
     */
    cache_out_filter_handle =
        ap_register_output_filter("CACHE_OUT",
                                  cache_out_filter,
                                  NULL,
                                  AP_FTYPE_CONTENT_SET+1);
    /*
     * CACHE_OUT_SUBREQ must go into the filter chain before SUBREQ_CORE to
     * handle subrequsts. Decrementing filter type by 1 ensures this
     * happens.
     */
    cache_out_subreq_filter_handle =
        ap_register_output_filter("CACHE_OUT_SUBREQ",
                                  cache_out_filter,
                                  NULL,
                                  AP_FTYPE_CONTENT_SET-1);
    /* CACHE_REMOVE_URL has to be a protocol filter to ensure that is
     * run even if the response is a canned error message, which
     * removes the content filters.
     */
    cache_remove_url_filter_handle =
        ap_register_output_filter("CACHE_REMOVE_URL",
                                  cache_remove_url_filter,
                                  NULL,
                                  AP_FTYPE_PROTOCOL);
    cache_invalidate_filter_handle =
        ap_register_output_filter("CACHE_INVALIDATE",
                                  cache_invalidate_filter,
                                  NULL,
                                  AP_FTYPE_PROTOCOL);
    ap_hook_post_config(cache_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
}