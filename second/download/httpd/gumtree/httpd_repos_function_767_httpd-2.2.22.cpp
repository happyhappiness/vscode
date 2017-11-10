const char *ssl_cmd_SSLInsecureRenegotiation(cmd_parms *cmd, void *dcfg, int flag)
{
#ifdef SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->insecure_reneg = flag?TRUE:FALSE;
    return NULL;
#else
    return "The SSLInsecureRenegotiation directive is not available "
        "with this SSL library";
#endif
}