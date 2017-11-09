static int stapling_mutex_reinit_helper(server_rec *s, apr_pool_t *p, 
                                        apr_global_mutex_t **mutex,
                                        const char *type)
{
    apr_status_t rv;
    const char *lockfile;

    lockfile = apr_global_mutex_lockfile(*mutex);
    if ((rv = apr_global_mutex_child_init(mutex,
                                          lockfile, p)) != APR_SUCCESS) {
        if (lockfile) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01946)
                         "Cannot reinit %s mutex with file `%s'",
                         type, lockfile);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01947)
                         "Cannot reinit %s mutex", type);
        }
        return FALSE;
    }
    return TRUE;
}