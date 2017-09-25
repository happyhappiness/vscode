                         mc->szMutexFile);
        else
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot create SSLMutex");
        return FALSE;
    }
#if !defined(OS2) && !defined(WIN32) && !defined(BEOS) && !defined(NETWARE)
    if (mc->szMutexFile && mc->ChownMutexFile == TRUE)
        chown(mc->szMutexFile, unixd_config.user_id, -1);
#endif

#if APR_HAS_SYSVSEM_SERIALIZE
#if APR_USE_SYSVSEM_SERIALIZE
    if (mc->nMutexMech == APR_LOCK_DEFAULT || 
        mc->nMutexMech == APR_LOCK_SYSVSEM) {
#else
    if (mc->nMutexMech == APR_LOCK_SYSVSEM) {
#endif
        rv = unixd_set_global_mutex_perms(mc->pMutex);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Could not set permissions on ssl_mutex; check User "
                         "and Group directives");
            return FALSE;
        }
    }
#endif
    return TRUE;
}

int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
