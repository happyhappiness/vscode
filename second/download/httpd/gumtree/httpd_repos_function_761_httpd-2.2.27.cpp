const char *ssl_cmd_SSLMutex(cmd_parms *cmd,
                             void *dcfg,
                             const char *arg_)
{
    const char *err;
    SSLModConfigRec *mc = myModConfig(cmd->server);
    /* Split arg_ into meth and file */
    char *meth = apr_pstrdup(cmd->temp_pool, arg_);
    char *file = strchr(meth, ':');
    if (file) {
        *(file++) = '\0';
        if (!*file) {
            file = NULL;
        }
    }

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    if (ssl_config_global_isfixed(mc)) {
        return NULL;
    }
    if (!strcasecmp(meth, "none") || !strcasecmp(meth, "no")) {
        mc->nMutexMode  = SSL_MUTEXMODE_NONE;
        return NULL;
    }

    /* APR determines temporary filename unless overridden below,
     * we presume file indicates an szMutexFile is a file path
     * unless the method sets szMutexFile=file and NULLs file
     */
    mc->nMutexMode  = SSL_MUTEXMODE_USED;
    mc->szMutexFile = NULL;

    /* NOTE: previously, 'yes' implied 'sem' */
    if (!strcasecmp(meth, "default") || !strcasecmp(meth, "yes")) {
        mc->nMutexMech = APR_LOCK_DEFAULT;
    }
#if APR_HAS_FCNTL_SERIALIZE
    else if ((!strcasecmp(meth, "fcntl") || !strcasecmp(meth, "file")) && file) {
        mc->nMutexMech = APR_LOCK_FCNTL;
    }
#endif
#if APR_HAS_FLOCK_SERIALIZE
    else if ((!strcasecmp(meth, "flock") || !strcasecmp(meth, "file")) && file) {
        mc->nMutexMech = APR_LOCK_FLOCK;
    }
#endif
#if APR_HAS_POSIXSEM_SERIALIZE
    else if (!strcasecmp(meth, "posixsem") || !strcasecmp(meth, "sem")) {
        mc->nMutexMech = APR_LOCK_POSIXSEM;
        /* Posix/SysV semaphores aren't file based, use the literal name
         * if provided and fall back on APR's default if not.  Today, APR
         * will ignore it, but once supported it has an absurdly short limit.
         */
        if (file) {
            mc->szMutexFile = apr_pstrdup(cmd->server->process->pool, file);

            file = NULL;
        }
    }
#endif
#if APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)
    else if (!strcasecmp(meth, "sysvsem") || !strcasecmp(meth, "sem")) {
        mc->nMutexMech = APR_LOCK_SYSVSEM;
    }
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
    else if (!strcasecmp(meth, "pthread")) {
        mc->nMutexMech = APR_LOCK_PROC_PTHREAD;
    }
#endif
    else {
        return apr_pstrcat(cmd->pool, "Invalid SSLMutex argument ", arg_,
                           " (", ssl_valid_ssl_mutex_string, ")", NULL);
    }

    /* Unless the method above assumed responsibility for setting up
     * mc->szMutexFile and NULLing out file, presume it is a file we
     * are looking to use
     */
    if (file) {
        mc->szMutexFile = ap_server_root_relative(cmd->server->process->pool, file);
        if (!mc->szMutexFile) {
            return apr_pstrcat(cmd->pool, "Invalid SSLMutex ", meth,
                               ": filepath ", file, NULL);
        }
    }

    return NULL;
}