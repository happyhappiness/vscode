    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                      "LDAP: SSL verify server certificate - %s",
                      mode?"TRUE":"FALSE");

    st->verify_svr_cert = mode;

    return(NULL);
