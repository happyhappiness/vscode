    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_daemons_limit = atoi(arg);
    return NULL;
}

static const char *set_server_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    server_limit = atoi(arg);
    return NULL;
}

static const command_rec prefork_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("StartServers", set_daemons_to_start, NULL, RSRC_CONF,
              "Number of child processes launched at server startup"),
AP_INIT_TAKE1("MinSpareServers", set_min_free_servers, NULL, RSRC_CONF,
              "Minimum number of idle children, to handle request spikes"),
AP_INIT_TAKE1("MaxSpareServers", set_max_free_servers, NULL, RSRC_CONF,
