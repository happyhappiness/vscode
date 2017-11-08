static const char *set_scriptlog_buffer(cmd_parms *cmd, void *dummy,
                                        const char *arg)
{
    server_rec *s = cmd->server;
    cgi_server_conf *conf = ap_get_module_config(s->module_config,
                                                 &cgi_module);

    conf->bufbytes = atoi(arg);
    return NULL;
}