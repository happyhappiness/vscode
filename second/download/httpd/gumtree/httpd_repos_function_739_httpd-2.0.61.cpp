const char *ssl_cmd_SSLCertificateFile(cmd_parms *cmd,
                                       void *dcfg,
                                       const char *arg)
{

    const char *err;

    if ((err = ssl_cmd_check_aidx_max(cmd, arg, SSL_AIDX_CERTS))) {
        return err;
    }

    return NULL;
}