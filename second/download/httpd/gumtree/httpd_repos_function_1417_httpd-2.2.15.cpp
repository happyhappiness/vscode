static const char *set_types_config(cmd_parms *cmd, void *dummy,
                                    const char *arg)
{
    ap_set_module_config(cmd->server->module_config, &mime_module,
                         (void *)arg);
    return NULL;
}