static const char *privs_mode(cmd_parms *cmd, void *dir, const char *arg)
{
    priv_mode mode = PRIV_UNSET;
    if (!strcasecmp(arg, "FAST")) {
        mode = PRIV_FAST;
    }
    else if (!strcasecmp(arg, "SECURE")) {
        mode = PRIV_SECURE;
    }
    else if (!strcasecmp(arg, "SELECTIVE")) {
        mode = PRIV_SELECTIVE;
    }

    if (cmd->path) {
        /* In a directory context, set the per_dir_config */
        priv_dir_cfg *cfg = dir;
        cfg->mode = mode;
        if ((mode == PRIV_UNSET) || (mode == PRIV_SELECTIVE)) {
            return "PrivilegesMode in a Directory context must be FAST or SECURE";
        }
    }
    else {
        /* In a global or vhost context, set the server config */
        priv_cfg *cfg = ap_get_module_config(cmd->server->module_config,
                                             &privileges_module);
        cfg->mode = mode;
        if (mode == PRIV_UNSET) {
            return "PrivilegesMode must be FAST, SECURE or SELECTIVE";
        }
    }
    return NULL;
}