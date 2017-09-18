    /* TODO: ap_configtestonly && ap_docrootcheck && */
    /* XXX Shouldn't this be relative to ServerRoot ??? */
    if (apr_filepath_merge((char**)&conf->ap_document_root, NULL, arg,
                           APR_FILEPATH_TRUENAME, cmd->pool) != APR_SUCCESS
        || !ap_is_directory(cmd->pool, arg)) {
        if (cmd->server->is_virtual) {
            ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0,
                          cmd->pool,
                          "Warning: DocumentRoot [%s] does not exist",
                          arg);
            conf->ap_document_root = arg;
        }
        else {
