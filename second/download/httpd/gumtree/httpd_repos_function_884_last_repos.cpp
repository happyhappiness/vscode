const char *ssl_cmd_SSLSRPVerifierFile(cmd_parms *cmd, void *dcfg,
                                       const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg)))
        return err;
    /* SRP_VBASE_init takes char*, not const char*  */
    sc->server->srp_vfile = apr_pstrdup(cmd->pool, arg);
    return NULL;
}