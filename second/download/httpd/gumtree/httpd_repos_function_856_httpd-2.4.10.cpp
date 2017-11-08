const char *ssl_cmd_SSLOpenSSLConfCmd(cmd_parms *cmd, void *dcfg,
                                      const char *arg1, const char *arg2)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    SSL_CONF_CTX *cctx = sc->server->ssl_ctx_config;
    int value_type = SSL_CONF_cmd_value_type(cctx, arg1);
    const char *err;
    ssl_ctx_param_t *param;

    if (value_type == SSL_CONF_TYPE_UNKNOWN) {
        return apr_psprintf(cmd->pool,
                            "'%s': invalid OpenSSL configuration command",
                            arg1);
    }

    if (value_type == SSL_CONF_TYPE_FILE) {
        if ((err = ssl_cmd_check_file(cmd, &arg2)))
            return err;
    }
    else if (value_type == SSL_CONF_TYPE_DIR) {
        if ((err = ssl_cmd_check_dir(cmd, &arg2)))
            return err;
    }

    param = apr_array_push(sc->server->ssl_ctx_param);
    param->name = arg1;
    param->value = arg2;
    return NULL;
}