const char *ssl_cmd_SSLEngine(cmd_parms *cmd, void *dcfg, const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    if (!strcasecmp(arg, "On")) {
        sc->enabled = SSL_ENABLED_TRUE;
        return NULL;
    }
    else if (!strcasecmp(arg, "Off")) {
        sc->enabled = SSL_ENABLED_FALSE;
        return NULL;
    }
    else if (!strcasecmp(arg, "Optional")) {
        sc->enabled = SSL_ENABLED_OPTIONAL;
        return NULL;
    }

    return "Argument must be On, Off, or Optional";
}