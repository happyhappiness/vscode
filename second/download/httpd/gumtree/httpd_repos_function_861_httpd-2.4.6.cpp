const char *ssl_cmd_SSLSRPUnknownUserSeed(cmd_parms *cmd, void *dcfg,
                                          const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    /* SRP_VBASE_new takes char*, not const char*  */
    sc->server->srp_unknown_user_seed = apr_pstrdup(cmd->pool, arg);
    return NULL;
}