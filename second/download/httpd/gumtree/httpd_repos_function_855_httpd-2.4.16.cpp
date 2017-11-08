const char *ssl_cmd_SSLOCSPResponderTimeout(cmd_parms *cmd, void *dcfg, const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->ocsp_responder_timeout = apr_time_from_sec(atoi(arg));
    if (sc->server->ocsp_responder_timeout < 0) {
        return "SSLOCSPResponderTimeout: invalid argument";
    }
    return NULL;
}