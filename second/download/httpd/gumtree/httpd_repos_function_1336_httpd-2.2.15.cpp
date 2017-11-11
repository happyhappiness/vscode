static const char *set_scriptlog_buffer(cmd_parms *cmd, void *dummy, const char *arg)
{
    server_rec *s = cmd->server;
    cgid_server_conf *conf = ap_get_module_config(s->module_config,
                                                  &cgid_module);

    conf->bufbytes = atoi(arg);
    return NULL;
}