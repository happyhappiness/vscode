static const char *vhost_group(cmd_parms *cmd, void *dir, const char *arg)
{
    priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                         &privileges_module);
    cfg->gid = ap_gname2id(arg);
    if (cfg->uid == 0) {
        return apr_pstrcat(cmd->pool, "Invalid groupid for VHostGroup: ",
                           arg, NULL);
    }
    return NULL;
}