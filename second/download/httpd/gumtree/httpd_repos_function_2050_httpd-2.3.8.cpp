static const char *set_reqtimeouts(cmd_parms *cmd, void *mconfig,
                                   const char *arg)
{
    reqtimeout_srv_cfg *conf =
    ap_get_module_config(cmd->server->module_config,
                         &reqtimeout_module);
    
    while (*arg) {
        char *word, *val;
        const char *err;
        
        word = ap_getword_conf(cmd->pool, &arg);
        val = strchr(word, '=');
        if (!val) {
            return "Invalid RequestReadTimeout parameter. Parameter must be "
            "in the form 'key=value'";
        }
        else
            *val++ = '\0';

        err = set_reqtimeout_param(conf, cmd->pool, word, val);
        
        if (err)
            return apr_psprintf(cmd->temp_pool, "RequestReadTimeout: %s=%s: %s",
                               word, val, err);
    }
    
    return NULL;
    
}