static const char *set_max_workers(cmd_parms * cmd, void *dummy,
                                   const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }
    if (!strcasecmp(cmd->cmd->name, "MaxClients")) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, APLOGNO(00521)
                     "MaxClients is deprecated, use MaxRequestWorkers "
                     "instead.");
    }
    max_workers = atoi(arg);
    return NULL;
}