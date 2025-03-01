const char *ssl_cmd_SSLOCSPEnable(cmd_parms *cmd, void *dcfg, int flag)
{   
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);

    sc->server->ocsp_enabled = flag ? TRUE : FALSE;

#ifndef HAVE_OCSP
    if (flag) {
        return "OCSP support not detected in SSL library; cannot enable "
            "OCSP validation";
    }
#endif    

    return NULL;
}