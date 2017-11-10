static void register_hooks(apr_pool_t *p)
{
    /* run after mod_deflate etc etc, but not at connection level, ie, mod_ssl. */
    ap_register_output_filter(RATE_LIMIT_FILTER_NAME, rate_limit_filter,
                              NULL, AP_FTYPE_PROTOCOL + 3);
}