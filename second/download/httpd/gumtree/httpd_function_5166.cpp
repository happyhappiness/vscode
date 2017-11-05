int ssl_stapling_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    const char *lockfile;

    if (mc->stapling_mutex == NULL) {
        return TRUE;
    }

    lockfile = apr_global_mutex_lockfile(mc->stapling_mutex);
    if ((rv = apr_global_mutex_child_init(&mc->stapling_mutex,
                                          lockfile, p)) != APR_SUCCESS) {
        if (lockfile) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01946)
                         "Cannot reinit %s mutex with file `%s'",
                         SSL_STAPLING_MUTEX_TYPE, lockfile);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01947)
                         "Cannot reinit %s mutex", SSL_STAPLING_MUTEX_TYPE);
        }
        return FALSE;
    }
    return TRUE;
}