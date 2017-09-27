
    /*
     * Filter program
     */
    else if (sc->server->pphrase_dialog_type == SSL_PPTYPE_FILTER) {
        const char *cmd = sc->server->pphrase_dialog_path;
        const char **argv = apr_palloc(p, sizeof(char *) * 4);
        char *result;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01969)
                     "Init: Requesting pass phrase from dialog filter "
                     "program (%s)", cmd);

        argv[0] = cmd;
        argv[1] = cpVHostID;
        argv[2] = cpAlgoType;
        argv[3] = NULL;

        result = ssl_util_readfilter(s, p, cmd, argv);
        apr_cpystrn(buf, result, bufsize);
        len = strlen(buf);
    }

    /*
     * Ok, we now have the pass phrase, so give it back
     */
    *cppPassPhraseCur = apr_pstrdup(p, buf);

    /*
     * And return its length to OpenSSL...
     */
    return (len);
}
