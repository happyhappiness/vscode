static int core_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap_set_version(pconf);
    ap_setup_make_content_type(pconf);
    return OK;
}