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

    /* We don't want to take into account whether or not KeepAliveTimeout is
     * set for the main server, because if no http_module directive is used
     * for a vhost, it will inherit the http_srv_cfg from the main server.
     * However keep_alive_timeout_set helps determine whether the vhost should
     * use its own configured timeout or the one from the vhost delared first
     * on the same IP:port (ie. c->base_server, and the legacy behaviour).
     */
    if (cmd->server->is_virtual) {
        cmd->server->keep_alive_timeout_set = 1;
    }
    return NULL;
}