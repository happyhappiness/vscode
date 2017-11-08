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
        else if (!strcasecmp(w, "allowanyuri")) {
            options |= OPTION_ANYURI;
        }
        else if (!strcasecmp(w, "mergebase")) {
            options |= OPTION_MERGEBASE;
        }
        else {
            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                               w, "'", NULL);
        }
    }

    /* server command? set both global scope and base directory scope */
    if (cmd->path == NULL) { /* is server command */
        rewrite_perdir_conf *dconf = in_dconf;
        rewrite_server_conf *sconf =
            ap_get_module_config(cmd->server->module_config,
                                 &rewrite_module);

        sconf->options |= options;
        sconf->options_set = 1;
        sconf->redirect_limit = limit;
        dconf->options |= options;
        dconf->options_set = 1;
        dconf->redirect_limit = limit;
     }
    /* directory command? set directory scope only */
    else {                  /* is per-directory command */
        rewrite_perdir_conf *dconf = in_dconf;

        dconf->options |= options;
        dconf->options_set = 1;
        dconf->redirect_limit = limit;
    }
 
    return NULL;
}