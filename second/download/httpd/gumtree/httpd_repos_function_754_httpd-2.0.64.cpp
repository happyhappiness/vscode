const char *ssl_cmd_SSLSessionCache(cmd_parms *cmd,
                                    void *dcfg,
                                    const char *arg)
{
    SSLModConfigRec *mc = myModConfig(cmd->server);
    const char *err, *colon;
    char *cp, *cp2;
    int arglen = strlen(arg);

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    if (ssl_config_global_isfixed(mc)) {
        return NULL;
    }

    if (strcEQ(arg, "none")) {
        mc->nSessionCacheMode      = SSL_SCMODE_NONE;
        mc->szSessionCacheDataFile = NULL;
    }
    else if ((arglen > 4) && strcEQn(arg, "dbm:", 4)) {
        mc->nSessionCacheMode      = SSL_SCMODE_DBM;
        mc->szSessionCacheDataFile = ap_server_root_relative(mc->pPool, arg+4);
        if (!mc->szSessionCacheDataFile) {
            return apr_psprintf(cmd->pool,
                                "SSLSessionCache: Invalid cache file path %s",
                                arg+4);
        }
    }
    else if ((arglen > 6) && strcEQn(arg, "shmht:", 6)) {
#if !APR_HAS_SHARED_MEMORY
        return MODSSL_NO_SHARED_MEMORY_ERROR;
#endif
        mc->nSessionCacheMode = SSL_SCMODE_SHMHT;
        colon = ap_strchr_c(arg, ':');
        mc->szSessionCacheDataFile =
            ap_server_root_relative(mc->pPool, colon+1);
        if (!mc->szSessionCacheDataFile) {
            return apr_psprintf(cmd->pool,
                                "SSLSessionCache: Invalid cache file path %s",
                                colon+1);
        }
        mc->tSessionCacheDataTable = NULL;
        mc->nSessionCacheDataSize  = 1024*512; /* 512KB */

        if ((cp = strchr(mc->szSessionCacheDataFile, '('))) {
            *cp++ = NUL;

            if (!(cp2 = strchr(cp, ')'))) {
                return "SSLSessionCache: Invalid argument: "
                       "no closing parenthesis";
            }

            *cp2 = NUL;

            mc->nSessionCacheDataSize = atoi(cp);

            if (mc->nSessionCacheDataSize < 8192) {
                return "SSLSessionCache: Invalid argument: "
                       "size has to be >= 8192 bytes";
            }

            if (mc->nSessionCacheDataSize >= APR_SHM_MAXSIZE) {
                return apr_psprintf(cmd->pool,
                                    "SSLSessionCache: Invalid argument: "
                                    "size has to be < %d bytes on this "
                                    "platform", APR_SHM_MAXSIZE);
            }
        }
    }
    else if (((arglen > 4) && strcEQn(arg, "shm:", 4)) ||
             ((arglen > 6) && strcEQn(arg, "shmcb:", 6))) {
#if !APR_HAS_SHARED_MEMORY
        return MODSSL_NO_SHARED_MEMORY_ERROR;
#endif
        mc->nSessionCacheMode      = SSL_SCMODE_SHMCB;
        colon = ap_strchr_c(arg, ':');
        mc->szSessionCacheDataFile =
            ap_server_root_relative(mc->pPool, colon+1);
        if (!mc->szSessionCacheDataFile) {
            return apr_psprintf(cmd->pool,
                                "SSLSessionCache: Invalid cache file path %s",
                                colon+1);
        }
        mc->tSessionCacheDataTable = NULL;
        mc->nSessionCacheDataSize  = 1024*512; /* 512KB */

        if ((cp = strchr(mc->szSessionCacheDataFile, '('))) {
            *cp++ = NUL;

            if (!(cp2 = strchr(cp, ')'))) {
                return "SSLSessionCache: Invalid argument: "
                       "no closing parenthesis";
            }

            *cp2 = NUL;

            mc->nSessionCacheDataSize = atoi(cp);

            if (mc->nSessionCacheDataSize < 8192) {
                return "SSLSessionCache: Invalid argument: "
                       "size has to be >= 8192 bytes";

            }

            if (mc->nSessionCacheDataSize >= APR_SHM_MAXSIZE) {
                return apr_psprintf(cmd->pool,
                                    "SSLSessionCache: Invalid argument: "
                                    "size has to be < %d bytes on this "
                                    "platform", APR_SHM_MAXSIZE);

            }
        }
    }
    else {
        return "SSLSessionCache: Invalid argument";
    }

    return NULL;
}