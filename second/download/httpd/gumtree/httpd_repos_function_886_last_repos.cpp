const char *ssl_cmd_SSLOCSPResponderCertificateFile(cmd_parms *cmd, void *dcfg, 
					   const char *arg)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
    const char *err;

    if ((err = ssl_cmd_check_file(cmd, &arg))) {
        return err;
    }

    sc->server->ocsp_certs_file = arg;
    return NULL;
}