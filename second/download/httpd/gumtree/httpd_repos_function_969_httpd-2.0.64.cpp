static const char *cmd_rewriteoptions(cmd_parms *cmd,
                                      void *in_dconf, const char *option)
{
    int options = 0, limit = 0;
    char *w;

    while (*option) {
        w = ap_getword_conf(cmd->pool, &option);

        if (!strcasecmp(w, "inherit")) {
            options |= OPTION_INHERIT;
        }
        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
            limit = atoi(&w[13]);
            if (limit <= 0) {
                return "RewriteOptions: MaxRedirects takes a number greater "
                       "than zero.";
            }
        }
        else if (!strcasecmp(w, "MaxRedirects")) { /* be nice */
            return "RewriteOptions: MaxRedirects has the format MaxRedirects"
                   "=n.";
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
        conf->redirect_limit = limit;
    }
    else {                  /* is per-directory command */
        rewrite_perdir_conf *conf = in_dconf;

        conf->options |= options;
        conf->redirect_limit = limit;
    }

    return NULL;
}