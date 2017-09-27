     */
    else if (sc->server->pphrase_dialog_type == SSL_PPTYPE_FILTER) {
        const char *cmd = sc->server->pphrase_dialog_path;
        const char **argv = apr_palloc(p, sizeof(char *) * 4);
        char *result;

        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Init: Requesting pass phrase from dialog filter "
                     "program (%s)", cmd);

        argv[0] = cmd;
        argv[1] = cpVHostID;
        argv[2] = cpAlgoType;
