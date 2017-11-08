static const char *add_module_info(cmd_parms * cmd, void *dummy,
                                   const char *name, const char *info)
{
    server_rec *s = cmd->server;
    info_svr_conf *conf =
        (info_svr_conf *) ap_get_module_config(s->module_config,
                                               &info_module);
    info_entry *new = apr_array_push(conf->more_info);

    new->name = name;
    new->info = info;
    return NULL;
}