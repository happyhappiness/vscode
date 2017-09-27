{
    rewrite_perdir_conf *dconf = in_dconf;
    rewrite_server_conf *sconf;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    if (cmd->path == NULL) { /* is server command */
        sconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
    }
    else                   /* is per-directory command */ {
        dconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
    }

    return NULL;
}

static const char *cmd_rewriteoptions(cmd_parms *cmd,
                                      void *in_dconf, const char *option)
{
    int options = 0;
    char *w;

    while (*option) {
        w = ap_getword_conf(cmd->pool, &option);

        if (!strcasecmp(w, "inherit")) {
            options |= OPTION_INHERIT;
        }
        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "RewriteOptions: MaxRedirects option has been "
                         "removed in favor of the global "
                         "LimitInternalRecursion directive and will be "
                         "ignored.");
        }
        else {
            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                               w, "'", NULL);
        }
    }

    /* put it into the appropriate config */
    if (cmd->path == NULL) { /* is server command */
        rewrite_server_conf *conf =
            ap_get_module_config(cmd->server->module_config,
                                 &rewrite_module);

        conf->options |= options;
    }
    else {                  /* is per-directory command */
        rewrite_perdir_conf *conf = in_dconf;

        conf->options |= options;
    }

    return NULL;
}

static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
