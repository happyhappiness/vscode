static const char *vhost_cgimode(cmd_parms *cmd, void *dir, const char *arg)
{
    priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                         &privileges_module);
    if (!strcasecmp(arg, "on")) {
        /* default - nothing to do */
    }
    else if (!strcasecmp(arg, "off")) {
        /* drop fork+exec privs */
        CFG_CHECK(priv_delset(cfg->priv, PRIV_PROC_FORK));
        CFG_CHECK(priv_delset(cfg->priv, PRIV_PROC_EXEC));
    }
    else if (!strcasecmp(arg, "secure")) {
        /* deny privileges to CGI procs */
        CFG_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_FORK));
        CFG_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_EXEC));
        CFG_CHECK(priv_delset(cfg->child_priv, PRIV_FILE_LINK_ANY));
        CFG_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_INFO));
        CFG_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_SESSION));
    }
    else {
        return "VHostCGIMode must be On, Off or Secure";
    }

    return NULL;
}