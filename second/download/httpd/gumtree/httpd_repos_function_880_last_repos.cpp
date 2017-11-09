const char *ssl_cmd_SSLStaplingFakeTryLater(cmd_parms *cmd,
                                            void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->server->stapling_fake_trylater = flag ? TRUE : FALSE;
    return NULL;
}