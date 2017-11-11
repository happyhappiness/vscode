static const char *set_magicfile(cmd_parms *cmd, void *dummy, const char *arg)
{
    magic_server_config_rec *conf = (magic_server_config_rec *)
    ap_get_module_config(cmd->server->module_config,
		      &mime_magic_module);

    if (!conf) {
	return MODNAME ": server structure not allocated";
    }
    conf->magicfile = arg;
    return NULL;
}