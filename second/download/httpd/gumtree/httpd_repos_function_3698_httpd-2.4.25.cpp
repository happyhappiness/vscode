static int authz_host_pre_config(apr_pool_t *p, apr_pool_t *plog,
                                 apr_pool_t *ptemp)
{
    /* we only use this hash in the parse config phase, ptemp is enough */
    parsed_subnets = apr_hash_make(ptemp);

    apr_ipsubnet_create(&localhost_v4, "127.0.0.0", "8", p);
    apr_hash_set(parsed_subnets, "127.0.0.0/8", APR_HASH_KEY_STRING, localhost_v4);

#if APR_HAVE_IPV6
    apr_ipsubnet_create(&localhost_v6, "::1", NULL, p);
    apr_hash_set(parsed_subnets, "::1", APR_HASH_KEY_STRING, localhost_v6);
#endif

    return OK;
}