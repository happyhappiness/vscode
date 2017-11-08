static int authz_host_post_config(apr_pool_t *p, apr_pool_t *plog,
                                  apr_pool_t *ptemp, server_rec *s)
{
    /* make sure we don't use this during .htaccess parsing */
    parsed_subnets = NULL;

    return OK;
}