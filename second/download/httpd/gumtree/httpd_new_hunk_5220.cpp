    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server, APLOGNO(02173)
                     "Invalid parameters for %s", cmd->cmd->name);
        return;
    }

    if (arg2 && (*(str = ap_getword_conf(cmd->pool, &arg2)) != '\0')) {
        max = atol(str);
    }

    /* if we aren't running as root, cannot increase max */
    if (geteuid()) {
        limit->rlim_cur = cur;
