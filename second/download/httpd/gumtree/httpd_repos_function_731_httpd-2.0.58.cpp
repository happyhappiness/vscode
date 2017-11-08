const char *ssl_cmd_SSLCryptoDevice(cmd_parms *cmd,
                                    void *dcfg,
                                    const char *arg)
{
    SSLModConfigRec *mc = myModConfig(cmd->server);
    const char *err;
    ENGINE *e;
#if SSL_LIBRARY_VERSION >= 0x00907000
    static int loaded_engines = FALSE;

    /* early loading to make sure the engines are already 
       available for ENGINE_by_id() above... */
    if (!loaded_engines) {
        ENGINE_load_builtin_engines();
        loaded_engines = TRUE;
    }
#endif
    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

    if (strcEQ(arg, "builtin")) {
        mc->szCryptoDevice = NULL;
    }
    else if ((e = ENGINE_by_id(arg))) {
        mc->szCryptoDevice = arg;
        ENGINE_free(e);
    }
    else {
        return "SSLCryptoDevice: Invalid argument";
    }

    return NULL;
}