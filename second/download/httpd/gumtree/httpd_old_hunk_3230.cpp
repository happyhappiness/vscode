static int stapling_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_lock(mc->stapling_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                     "Failed to acquire OCSP stapling lock");
        return FALSE;
    }
    return TRUE;
}

static int stapling_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_unlock(mc->stapling_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                     "Failed to release OCSP stapling lock");
        return FALSE;
    }
    return TRUE;
}

