     * like CacheModule  mem_cache_module | file_cache_module, etc,
     * which would cause the approprpriate cache module to be loaded.
     * This is more intuitive that requiring a LoadModule directive.
     */

    AP_INIT_FLAG("CacheOn", set_cache_on, NULL, RSRC_CONF,
                 "On if the transparent cache should be enabled"),
    AP_INIT_TAKE2("CacheEnable", add_cache_enable, NULL, RSRC_CONF,
                  "A cache type and partial URL prefix below which "
                  "caching is enabled"),
    AP_INIT_TAKE1("CacheDisable", add_cache_disable, NULL, RSRC_CONF,
                  "A partial URL prefix below which caching is disabled"),
    AP_INIT_TAKE1("CacheMaxExpire", set_cache_maxex, NULL, RSRC_CONF,
                  "The maximum time in seconds to cache a document"),
     AP_INIT_TAKE1("CacheDefaultExpire", set_cache_defex, NULL, RSRC_CONF,
                   "The default time in seconds to cache a document"),
     AP_INIT_FLAG("CacheIgnoreNoLastMod", set_cache_ignore_no_last_mod, NULL, 
                  RSRC_CONF, 
                  "Ignore Responses where there is no Last Modified Header"),
     AP_INIT_FLAG("CacheIgnoreCacheControl", set_cache_ignore_cachecontrol,
                  NULL, 
                  RSRC_CONF, 
                  "Ignore requests from the client for uncached content"),
    AP_INIT_TAKE1("CacheLastModifiedFactor", set_cache_factor, NULL, RSRC_CONF,
                  "The factor used to estimate Expires date from "
                  "LastModified date"),
    AP_INIT_TAKE1("CacheForceCompletion", set_cache_complete, NULL, RSRC_CONF,
                  "Percentage of download to arrive for the cache to force "
                  "complete transfer"),
    {NULL}
};

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
    ap_register_output_filter("CACHE_IN", 
                              cache_in_filter, 
                              NULL,
                              AP_FTYPE_CONTENT_SET);
    /* CACHE_OUT must go into the filter chain before SUBREQ_CORE to
     * handle subrequsts. Decrementing filter type by 1 ensures this 
     * happens.
     */
    ap_register_output_filter("CACHE_OUT", 
                              cache_out_filter, 
                              NULL,
                              AP_FTYPE_CONTENT_SET-1);
    ap_register_output_filter("CACHE_CONDITIONAL", 
                              cache_conditional_filter, 
                              NULL,
                              AP_FTYPE_CONTENT_SET);
    ap_hook_post_config(cache_post_config, NULL, NULL, APR_HOOK_REALLY_FIRST);
}

module AP_MODULE_DECLARE_DATA cache_module =
{
