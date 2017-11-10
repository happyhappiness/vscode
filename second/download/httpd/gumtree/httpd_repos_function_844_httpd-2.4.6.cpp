const char *ssl_cmd_SSLOCSPResponseMaxAge(cmd_parms *cmd, void *dcfg, const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->ocsp_resp_maxage = atoi(arg);
    if (sc->server->ocsp_resp_maxage < 0) {
        return "SSLOCSPResponseMaxAge: invalid argument";
    }
    return NULL;
}