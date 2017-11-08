const char *ssl_cmd_SSLHonorCipherOrder(cmd_parms *cmd, void *dcfg, int flag)
{
#ifdef SSL_OP_CIPHER_SERVER_PREFERENCE
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    sc->cipher_server_pref = flag?TRUE:FALSE;
    return NULL;
#else
    return "SSLHonorCiperOrder unsupported; not implemented by the SSL library";
#endif
}