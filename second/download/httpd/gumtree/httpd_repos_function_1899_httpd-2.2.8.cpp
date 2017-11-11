static int initialize_module(apr_pool_t *p, apr_pool_t *plog,
                             apr_pool_t *ptemp, server_rec *s)
{
    void *data;
    const char *userdata_key = "auth_digest_init";

    /* initialize_module() will be called twice, and if it's a DSO
     * then all static data from the first call will be lost. Only
     * set up our static data on the second call. */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);
        return OK;
    }
    if (initialize_secret(s) != APR_SUCCESS) {
        return !OK;
    }

#if APR_HAS_SHARED_MEMORY
    /* Note: this stuff is currently fixed for the lifetime of the server,
     * i.e. even across restarts. This means that A) any shmem-size
     * configuration changes are ignored, and B) certain optimizations,
     * such as only allocating the smallest necessary entry for each
     * client, can't be done. However, the alternative is a nightmare:
     * we can't call apr_shm_destroy on a graceful restart because there
     * will be children using the tables, and we also don't know when the
     * last child dies. Therefore we can never clean up the old stuff,
     * creating a creeping memory leak.
     */
    initialize_tables(s, p);
    apr_pool_cleanup_register(p, NULL, cleanup_tables, apr_pool_cleanup_null);
#endif  /* APR_HAS_SHARED_MEMORY */
    return OK;
}