static const char *vhost_user(cmd_parms *cmd, void *dir, const char *arg)
{
    priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                         &privileges_module);
    cfg->uid = ap_uname2id(arg);
    if (cfg->uid == 0) {
        return apr_pstrcat(cmd->pool, "Invalid userid for VHostUser: ",
                           arg, NULL);
    }
    return NULL;
}