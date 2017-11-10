const char *ssl_cmd_SSLProxyCheckPeerExpire(cmd_parms *cmd, void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->proxy_ssl_check_peer_expire = flag ? SSL_ENABLED_TRUE : SSL_ENABLED_FALSE;

    return NULL;
}