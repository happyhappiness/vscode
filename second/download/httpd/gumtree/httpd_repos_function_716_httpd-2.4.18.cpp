static int stapling_mutex_off(server_rec *s, apr_global_mutex_t *mutex,
                              const char *name)
{
    apr_status_t rv;

    if ((rv = apr_global_mutex_unlock(mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01949)
                     "Failed to release OCSP %s lock", name);
        return FALSE;
    }
    return TRUE;
}