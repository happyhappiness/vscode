static void *create_deflate_dirconf(apr_pool_t *p, char *dummy)
{
    deflate_dirconf_t *dc = apr_pcalloc(p, sizeof(*dc));
    dc->ratio_limit = AP_INFLATE_RATIO_LIMIT;
    dc->ratio_burst = AP_INFLATE_RATIO_BURST;
    return dc;
}