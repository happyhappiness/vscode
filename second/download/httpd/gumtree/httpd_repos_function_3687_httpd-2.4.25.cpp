static int fcgi_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                           apr_pool_t *ptemp)
{
    fcgi_authn_providers = apr_hash_make(pconf);
    fcgi_authz_providers = apr_hash_make(pconf);

    return OK;
}