static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(DATA_FILTER, data_out_filter, NULL,
            AP_FTYPE_RESOURCE);
}