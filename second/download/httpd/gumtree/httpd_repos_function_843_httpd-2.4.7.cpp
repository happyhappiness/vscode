const char *ssl_cmd_SSLOCSPResponseTimeSkew(cmd_parms *cmd, void *dcfg, const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->ocsp_resptime_skew = atoi(arg);
    if (sc->server->ocsp_resptime_skew < 0) {
        return "SSLOCSPResponseTimeSkew: invalid argument";
    }
    return NULL;
}