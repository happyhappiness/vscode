
    /*
     * Filter program
     */
    else if (sc->server->pphrase_dialog_type == SSL_PPTYPE_FILTER) {
        const char *cmd = sc->server->pphrase_dialog_path;
        const char **argv = apr_palloc(ppcb_arg->p, sizeof(char *) * 3);
        char *result;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, ppcb_arg->s, APLOGNO(01969)
                     "Init: Requesting pass phrase from dialog filter "
                     "program (%s)", cmd);

        argv[0] = cmd;
        argv[1] = ppcb_arg->key_id;
        argv[2] = NULL;

        result = ssl_util_readfilter(ppcb_arg->s, ppcb_arg->p, cmd, argv);
        apr_cpystrn(buf, result, bufsize);
        len = strlen(buf);
    }

