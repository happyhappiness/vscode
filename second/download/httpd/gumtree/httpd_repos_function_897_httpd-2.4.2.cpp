int ssl_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    /* A mutex is only needed if a session cache is configured, and
     * the provider used is not internally multi-process/thread
     * safe. */
    if (!mc->sesscache
        || (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) == 0) {
        return TRUE;
    }

    if (mc->pMutex) {
        return TRUE;
    }

    if ((rv = ap_global_mutex_create(&mc->pMutex, NULL, SSL_CACHE_MUTEX_TYPE,
                                     NULL, s, s->process->pool, 0))
            != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}