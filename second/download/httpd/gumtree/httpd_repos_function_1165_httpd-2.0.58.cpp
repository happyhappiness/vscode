static const char *set_script_socket(cmd_parms *cmd, void *dummy, const char *arg) 
{ 
    server_rec *s = cmd->server; 
    cgid_server_conf *conf = ap_get_module_config(s->module_config,
                                                  &cgid_module); 

    conf->sockname = ap_server_root_relative(cmd->pool, arg); 

    if (!conf->sockname) {
        return apr_pstrcat(cmd->pool, "Invalid Scriptsock path ",
                           arg, NULL);
    }

    return NULL; 
}