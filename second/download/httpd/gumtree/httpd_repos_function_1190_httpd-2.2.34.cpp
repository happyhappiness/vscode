static const char *cmd_rewriteengine(cmd_parms *cmd,
                                     void *in_dconf, int flag)
{
    rewrite_perdir_conf *dconf = in_dconf;
    rewrite_server_conf *sconf;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    /* server command? set both global scope and base directory scope */
    if (cmd->path == NULL) {
        sconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
        sconf->state_set = 1;
        dconf->state = sconf->state;
        dconf->state_set = 1;
    }
    /* directory command? set directory scope only */
    else {
        dconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
        dconf->state_set = 1;
    }

    return NULL;
}