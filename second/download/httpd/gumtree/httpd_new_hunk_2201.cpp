        return err;
    }

    /* Throw a warning if we're in <Location> or <Files> */
    if (ap_check_cmd_context(cmd, NOT_IN_LOCATION | NOT_IN_FILES)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Useless use of AllowOverride in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);
    }

    d->override = OR_NONE;
    while (l[0]) {
        w = ap_getword_conf(cmd->pool, &l);

