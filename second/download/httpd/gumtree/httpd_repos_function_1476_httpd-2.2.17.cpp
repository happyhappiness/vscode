static int balancer_init(apr_pool_t *p, apr_pool_t *plog,
                         apr_pool_t *ptemp, server_rec *s)
{
    void *data;
    const char *userdata_key = "mod_proxy_balancer_init";
    apr_uuid_t uuid;

    /* balancer_init() will be called twice during startup.  So, only
     * set up the static data the second time through. */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);
        return OK;
    }

    /* Retrieve a UUID and store the nonce for the lifetime of
     * the process. */
    apr_uuid_get(&uuid);
    apr_uuid_format(balancer_nonce, &uuid);

    return OK;
}