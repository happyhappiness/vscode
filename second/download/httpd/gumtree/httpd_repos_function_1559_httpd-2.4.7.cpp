static int pre_config(apr_pool_t *pconf,
                      apr_pool_t *plog,
                      apr_pool_t *ptemp)
{
    APR_OPTIONAL_FN_TYPE(ap_register_rewrite_mapfunc) *map_pfn_register;

    ap_mutex_register(pconf, rewritemap_mutex_type, NULL, APR_LOCK_DEFAULT, 0);

    /* register int: rewritemap handlers */
    map_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_rewrite_mapfunc);
    if (map_pfn_register) {
        map_pfn_register("tolower", rewrite_mapfunc_tolower);
        map_pfn_register("toupper", rewrite_mapfunc_toupper);
        map_pfn_register("escape", rewrite_mapfunc_escape);
        map_pfn_register("unescape", rewrite_mapfunc_unescape);
    }
    dbd_acquire = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_acquire);
    dbd_prepare = APR_RETRIEVE_OPTIONAL_FN(ap_dbd_prepare);
    return OK;
}