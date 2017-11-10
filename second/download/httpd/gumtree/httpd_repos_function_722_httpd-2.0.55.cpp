const char *ssl_cmd_SSLMutex(cmd_parms *cmd,
                             void *dcfg,
                             const char *arg)
{
    const char *err;
    SSLModConfigRec *mc = myModConfig(cmd->server);

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    if (ssl_config_global_isfixed(mc)) {
        return NULL;
    }

    if (strcEQ(arg, "none") || strcEQ(arg, "no")) {
        mc->nMutexMode  = SSL_MUTEXMODE_NONE;
    }
    /* NOTE: previously, 'yes' implied 'sem' */
    else if (strcEQ(arg, "default") || strcEQ(arg, "yes")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_DEFAULT;
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
#if APR_HAS_FLOCK_SERIALIZE
    else if (strlen(arg) > 6 && strcEQn(arg, "flock:", 6)) {
        const char *file = ap_server_root_relative(cmd->pool, arg+6);
        if (!file) {
            return apr_pstrcat(cmd->pool, "Invalid SSLMutex flock: path ", 
                               arg+6, NULL);
        }
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_FLOCK;
        mc->szMutexFile = apr_psprintf(mc->pPool, "%s.%lu",
                                       file, (unsigned long)getpid());
    }
#endif
#if APR_HAS_FCNTL_SERIALIZE
    else if (strlen(arg) > 6 && strcEQn(arg, "fcntl:", 6)) {
        const char *file = ap_server_root_relative(cmd->pool, arg+6);
        if (!file) {
            return apr_pstrcat(cmd->pool, "Invalid SSLMutex fcntl: path ", 
                               arg+6, NULL);
        }
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_FCNTL;
        mc->szMutexFile = apr_psprintf(mc->pPool, "%s.%lu",
                                       file, (unsigned long)getpid());
    }
#endif
#if APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)
    else if (strcEQ(arg, "sysvsem")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_SYSVSEM;
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
#endif
#if APR_HAS_POSIXSEM_SERIALIZE
    else if (strcEQ(arg, "posixsem")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_POSIXSEM;
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    else if (strcEQ(arg, "pthread")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->nMutexMech = APR_LOCK_PROC_PTHREAD;
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
#endif
#if APR_HAS_FLOCK_SERIALIZE || APR_HAS_FCNTL_SERIALIZE
    else if (strlen(arg) > 5 && strcEQn(arg, "file:", 5)) {
        const char *file = ap_server_root_relative(cmd->pool, arg+5);
        if (!file) {
            return apr_pstrcat(cmd->pool, "Invalid SSLMutex file: path ", 
                               arg+5, NULL);
        }
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
#if APR_HAS_FLOCK_SERIALIZE
        mc->nMutexMech  = APR_LOCK_FLOCK;
#endif
#if APR_HAS_FCNTL_SERIALIZE
        mc->nMutexMech  = APR_LOCK_FCNTL;
#endif
        mc->szMutexFile =
            apr_psprintf(mc->pPool, "%s.%lu",
                         file, (unsigned long)getpid());
    }
#endif
#if (APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)) || APR_HAS_POSIXSEM_SERIALIZE
    else if (strcEQ(arg, "sem")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
#if APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)
        mc->nMutexMech  = APR_LOCK_SYSVSEM;
#endif
#if APR_HAS_POSIXSEM_SERIALIZE
        mc->nMutexMech  = APR_LOCK_POSIXSEM;
#endif
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
#endif
    else {
        return apr_pstrcat(cmd->pool, "Invalid SSLMutex argument ", 
                           arg, " (", ssl_valid_ssl_mutex_string, ")", NULL);
    }

    return NULL;
}