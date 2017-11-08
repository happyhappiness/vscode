const char *ssl_cmd_SSLRequireSSL(cmd_parms *cmd, void *dcfg)
{
    SSLDirConfigRec *dc = (SSLDirConfigRec *)dcfg;

    dc->bSSLRequired = TRUE;

    return NULL;
}