int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    const char *lockfile;

    if (mc->pMutex == NULL || !mc->sesscache
        || (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) == 0) {
        return TRUE;
    }

    lockfile = apr_global_mutex_lockfile(mc->pMutex);
    if ((rv = apr_global_mutex_child_init(&mc->pMutex,
                                          lockfile,
                                          p)) != APR_SUCCESS) {
        if (lockfile)
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot reinit %s mutex with file `%s'",
                         SSL_CACHE_MUTEX_TYPE, lockfile);
        else
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                         "Cannot reinit %s mutex", SSL_CACHE_MUTEX_TYPE);
        return FALSE;
    }
    return TRUE;
}