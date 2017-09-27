    apr_status_t rv;

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
        return TRUE;
    if ((rv = apr_global_mutex_unlock(mc->pMutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
                     "Failed to release global mutex lock");
        return FALSE;
    }
    return TRUE;
}

