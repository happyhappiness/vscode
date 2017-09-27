        --*recursion;
    }

    return NULL;
}

static const char *set_loglevel(cmd_parms *cmd, void *dummy, const char *arg)
{
    char *str;

    const char *err = ap_check_cmd_context(cmd,
                                           NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);
    if (err != NULL) {
        return err;
    }

    if ((str = ap_getword_conf(cmd->pool, &arg))) {
        if (!strcasecmp(str, "emerg")) {
            cmd->server->loglevel = APLOG_EMERG;
        }
        else if (!strcasecmp(str, "alert")) {
            cmd->server->loglevel = APLOG_ALERT;
        }
        else if (!strcasecmp(str, "crit")) {
            cmd->server->loglevel = APLOG_CRIT;
        }
        else if (!strcasecmp(str, "error")) {
            cmd->server->loglevel = APLOG_ERR;
        }
        else if (!strcasecmp(str, "warn")) {
            cmd->server->loglevel = APLOG_WARNING;
        }
        else if (!strcasecmp(str, "notice")) {
            cmd->server->loglevel = APLOG_NOTICE;
        }
        else if (!strcasecmp(str, "info")) {
            cmd->server->loglevel = APLOG_INFO;
        }
        else if (!strcasecmp(str, "debug")) {
            cmd->server->loglevel = APLOG_DEBUG;
        }
        else {
            return "LogLevel requires level keyword: one of "
                   "emerg/alert/crit/error/warn/notice/info/debug";
        }
    }
    else {
        return "LogLevel requires level keyword";
    }

    return NULL;
}

AP_DECLARE(const char *) ap_psignature(const char *prefix, request_rec *r)
{
    char sport[20];
