    return TRUE;
}

int ssl_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
        return TRUE;
    if (apr_global_mutex_lock(mc->pMutex) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_WARN, "Failed to acquire global mutex lock");
        return FALSE;
    }
    return TRUE;
}

int ssl_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
        return TRUE;
    if (apr_global_mutex_unlock(mc->pMutex) != APR_SUCCESS) {
        ssl_log(s, SSL_LOG_WARN, "Failed to release global mutex lock");
        return FALSE;
    }
    return TRUE;
}

