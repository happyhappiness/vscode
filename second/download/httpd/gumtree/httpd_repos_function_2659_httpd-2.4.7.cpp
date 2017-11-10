static const char *vhost_cgiprivs(cmd_parms *cmd, void *dir, const char *arg)
{
    priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                         &privileges_module);
    const char *priv = arg;
    if (*priv == '-') {
        CFG_CHECK(priv_delset(cfg->child_priv, priv+1));
    }
    else if (*priv == '+') {
        CFG_CHECK(priv_addset(cfg->child_priv, priv+1));
    }
    else {
        priv_emptyset(cfg->child_priv);
        CFG_CHECK(priv_addset(cfg->child_priv, priv));
    }
    return NULL;
}