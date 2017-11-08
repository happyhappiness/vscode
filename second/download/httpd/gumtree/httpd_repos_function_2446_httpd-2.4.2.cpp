static const char *vhost_secure(cmd_parms *cmd, void *dir, int arg)
{
    priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                         &privileges_module);
    if (!arg) {
        /* add basic privileges, excluding those covered by cgimode */
        CFG_CHECK(priv_addset(cfg->priv, PRIV_FILE_LINK_ANY));
        CFG_CHECK(priv_addset(cfg->priv, PRIV_PROC_INFO));
        CFG_CHECK(priv_addset(cfg->priv, PRIV_PROC_SESSION));
    }
    return NULL;
}