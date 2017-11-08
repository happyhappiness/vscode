static const char *dumpio_enable_input(cmd_parms *cmd, void *dummy, int arg)
{
    dumpio_conf_t *ptr =
    (dumpio_conf_t *) ap_get_module_config(cmd->server->module_config,
                                           &dumpio_module);

    ptr->enable_input = arg;
    return NULL;
}