    }

    /* recursion state: ok */
    return 0;
}

static const char *set_trace_enable(cmd_parms *cmd, void *dummy,
                                    const char *arg1)
{
    core_server_config *conf = ap_get_module_config(cmd->server->module_config,
                                                    &core_module);

