static void register_hooks(apr_pool_t *p)
{
    ap_register_output_filter("BROTLI_COMPRESS", compress_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
}