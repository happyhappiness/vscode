const char *ssl_cmd_SSLRenegBufferSize(cmd_parms *cmd, void *dcfg, const char *arg)
{
    SSLDirConfigRec *dc = dcfg;
    
    dc->nRenegBufferSize = atoi(arg);
    if (dc->nRenegBufferSize < 0) {
        return apr_pstrcat(cmd->pool, "Invalid size for SSLRenegBufferSize: ",
                           arg, NULL);
    }

    return NULL;
}