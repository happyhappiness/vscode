static const char *set_loglevel(cmd_parms *cmd, void *dummy, const char *arg)
{
    char *str;
    dumpio_conf_t *ptr =
    (dumpio_conf_t *) ap_get_module_config(cmd->server->module_config,
                                           &dumpio_module);

    const char *err = ap_check_cmd_context(cmd,
                                           NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);
    if (err != NULL) {
        return err;
    }

    if ((str = ap_getword_conf(cmd->pool, &arg))) {
        if (!strcasecmp(str, "emerg")) {
            ptr->loglevel = APLOG_EMERG;
        }
        else if (!strcasecmp(str, "alert")) {
            ptr->loglevel = APLOG_ALERT;
        }
        else if (!strcasecmp(str, "crit")) {
            ptr->loglevel = APLOG_CRIT;
        }
        else if (!strcasecmp(str, "error")) {
            ptr->loglevel = APLOG_ERR;
        }
        else if (!strcasecmp(str, "warn")) {
            ptr->loglevel = APLOG_WARNING;
        }
        else if (!strcasecmp(str, "notice")) {
            ptr->loglevel = APLOG_NOTICE;
        }
        else if (!strcasecmp(str, "info")) {
            ptr->loglevel = APLOG_INFO;
        }
        else if (!strcasecmp(str, "debug")) {
            ptr->loglevel = APLOG_DEBUG;
        }
        else {
            return "DumpIOLogLevel requires level keyword: one of "
                   "emerg/alert/crit/error/warn/notice/info/debug";
        }
    }
    else {
        return "DumpIOLogLevel requires level keyword";
    }

    return NULL;
}