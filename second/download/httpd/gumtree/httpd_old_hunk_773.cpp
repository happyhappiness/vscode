    sc->proxy->pkp->cert_path = arg;

    return NULL;
}


const char *ssl_cmd_SSLUserName(cmd_parms *cmd, void *dcfg, 
				const char *arg)
{
    SSLDirConfigRec *dc = (SSLDirConfigRec *)dcfg;
    dc->szUserName = arg;
    return NULL;
}
