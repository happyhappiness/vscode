        }
        else {
            cur = atol(str);
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
                     "Invalid parameters for %s", cmd->cmd->name);
        return;
    }

    if (arg2 && (str = ap_getword_conf(cmd->pool, &arg2))) {
        max = atol(str);
    }

    /* if we aren't running as root, cannot increase max */
    if (geteuid()) {
        limit->rlim_cur = cur;
        if (max) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, cmd->server,
                         "Must be uid 0 to raise maximum %s", cmd->cmd->name);
        }
    }
    else {
        if (cur) {
            limit->rlim_cur = cur;
