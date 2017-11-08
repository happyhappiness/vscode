const char *ssl_cmd_SSLFIPS(cmd_parms *cmd, void *dcfg, int flag)
{
#ifdef HAVE_FIPS
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
#endif
    const char *err;

    if ((err = ap_check_cmd_context(cmd, GLOBAL_ONLY))) {
        return err;
    }

#ifdef HAVE_FIPS
    if ((sc->fips != UNSET) && (sc->fips != (BOOL)(flag ? TRUE : FALSE)))
        return "Conflicting SSLFIPS options, cannot be both On and Off";
    sc->fips = flag ? TRUE : FALSE;
#else
    if (flag)
        return "SSLFIPS invalid, rebuild httpd and openssl compiled for FIPS";
#endif

    return NULL;
}