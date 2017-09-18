                         mc->szMutexFile);
        else
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                         "Cannot create SSLMutex");
        return FALSE;
    }
#if APR_HAS_FLOCK_SERIALIZE
    if (mc->szMutexFile && mc->ChownMutexFile == TRUE)
        chown(mc->szMutexFile, unixd_config.user_id, -1);
#endif

#if APR_HAS_SYSVSEM_SERIALIZE
#if APR_USE_SYSVSEM_SERIALIZE
