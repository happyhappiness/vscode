const char *ssl_cmd_SSLProxyCipherSuite(cmd_parms *cmd,
                                        void *dcfg,
                                        const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    /* always disable null and export ciphers */
    arg = apr_pstrcat(cmd->pool, arg, ":!aNULL:!eNULL:!EXP", NULL);

    sc->proxy->auth.cipher_suite = arg;

    return NULL;
}