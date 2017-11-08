const char *ssl_cmd_SSLOCSPProxyURL(cmd_parms *cmd, void *dcfg,
                                    const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->proxy_uri = apr_palloc(cmd->pool, sizeof(apr_uri_t));
    if (apr_uri_parse(cmd->pool, arg, sc->server->proxy_uri) != APR_SUCCESS) {
        return apr_psprintf(cmd->pool,
                            "SSLOCSPProxyURL: Cannot parse URL %s", arg);
    }
    return NULL;
}