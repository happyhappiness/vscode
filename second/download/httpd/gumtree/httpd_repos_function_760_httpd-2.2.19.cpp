const char *ssl_cmd_SSLCryptoDevice(cmd_parms *cmd,
                                    void *dcfg,
                                    const char *arg)
{
    SSLModConfigRec *mc = myModConfig(cmd->server);
    const char *err;
    ENGINE *e;

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
        err = "SSLCryptoDevice: Invalid argument; must be one of: "
              "'builtin' (none)";
        e = ENGINE_get_first();
        while (e) {
            ENGINE *en;
            err = apr_pstrcat(cmd->pool, err, ", '", ENGINE_get_id(e),
                                         "' (", ENGINE_get_name(e), ")", NULL);
            en = ENGINE_get_next(e);
            ENGINE_free(e);
            e = en;
        }
        return err;
    }

    return NULL;
}