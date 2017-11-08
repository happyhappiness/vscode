static const char *dumpio_enable_output(cmd_parms *cmd, void *dummy, int arg)
{
    dumpio_conf_t *ptr = ap_get_module_config(cmd->server->module_config,
                                              &dumpio_module);

    ptr->enable_output = arg;
    return NULL;
}