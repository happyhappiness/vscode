int ssl_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_unlock(mc->pMutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                     "Failed to release SSL session cache lock");
        return FALSE;
    }
    return TRUE;
}