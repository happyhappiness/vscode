static const char *cmd_rewriteoptions(cmd_parms *cmd,
                                      void *in_dconf, const char *option)
{
    rewrite_perdir_conf *dconf = in_dconf;
    rewrite_server_conf *sconf;
    const char *err;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    if (cmd->path == NULL) { /* is server command */
        err = cmd_rewriteoptions_setoption(cmd->pool,
                                           &(sconf->options), option);
    }
    else {                 /* is per-directory command */
        err = cmd_rewriteoptions_setoption(cmd->pool,
                                           &(dconf->options), option);
    }

    return err;
}