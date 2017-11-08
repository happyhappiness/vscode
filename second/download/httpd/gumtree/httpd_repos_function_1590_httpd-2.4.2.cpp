static const char *set_keep_alive_timeout(cmd_parms *cmd, void *dummy,
                                          const char *arg)
{
    apr_interval_time_t timeout;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    /* Stolen from mod_proxy.c */
    if (ap_timeout_parameter_parse(arg, &timeout, "s") != APR_SUCCESS)
        return "KeepAliveTimeout has wrong format";
    cmd->server->keep_alive_timeout = timeout;
    return NULL;
}