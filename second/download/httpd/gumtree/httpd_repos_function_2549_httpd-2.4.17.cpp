static void register_hooks(apr_pool_t *pool)
{
    ap_register_output_filter(substitute_filter_name, substitute_filter,
                              NULL, AP_FTYPE_RESOURCE);
}