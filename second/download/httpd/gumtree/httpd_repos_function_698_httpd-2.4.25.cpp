void ssl_stapling_certinfo_hash_init(apr_pool_t *p)
{
    stapling_certinfo = apr_hash_make(p);
}