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
    else if (strlen(arg) > 5 && strcEQn(arg, "file:", 5)) {
        const char *file = ap_server_root_relative(cmd->pool, arg+5);
        if (!file) {
            return apr_pstrcat(cmd->pool, "Invalid SSLMutex file: path ", 
                               arg+5, NULL);
        }
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->szMutexFile =
            apr_psprintf(mc->pPool, "%s.%lu",
                         file, (unsigned long)getpid());
    }
    else if (strcEQ(arg, "sem") || strcEQ(arg, "yes")) {
        mc->nMutexMode  = SSL_MUTEXMODE_USED;
        mc->szMutexFile = NULL; /* APR determines temporary filename */
    }
    else {
        return apr_pstrcat(cmd->pool, "Invalid SSLMutex argument ", 
                           arg, NULL);
    }

    return NULL;
}