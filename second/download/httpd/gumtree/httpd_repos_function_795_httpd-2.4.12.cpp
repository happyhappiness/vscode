const char *ssl_cmd_SSLCompression(cmd_parms *cmd, void *dcfg, int flag)
{
#if !defined(OPENSSL_NO_COMP)
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
#ifndef SSL_OP_NO_COMPRESSION
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err)
        return "This version of openssl does not support configuring "
               "compression within <VirtualHost> sections.";
#endif
    sc->compression = flag ? TRUE : FALSE;
    return NULL;
#else
    return "Setting Compression mode unsupported; not implemented by the SSL library";
#endif
}