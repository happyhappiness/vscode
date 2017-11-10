static const char *set_trace_enable(cmd_parms *cmd, void *dummy,
                                    const char *arg1)
{
    core_server_config *conf = ap_get_module_config(cmd->server->module_config,
                                                    &core_module);

    if (strcasecmp(arg1, "on") == 0) {
        conf->trace_enable = AP_TRACE_ENABLE;
    }
    else if (strcasecmp(arg1, "off") == 0) {
        conf->trace_enable = AP_TRACE_DISABLE;
    }
    else if (strcasecmp(arg1, "extended") == 0) {
        conf->trace_enable = AP_TRACE_EXTENDED;
    }
    else {
        return "TraceEnable must be one of 'on', 'off', or 'extended'";
    }

    return NULL;
}