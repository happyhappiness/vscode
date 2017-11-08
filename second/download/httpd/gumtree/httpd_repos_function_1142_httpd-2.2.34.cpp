static const char *set_user_dir(cmd_parms *cmd, void *dummy, const char *arg)
{
    userdir_config *s_cfg = ap_get_module_config(cmd->server->module_config,
                                                 &userdir_module);
    char *username;
    const char *usernames = arg;
    char *kw = ap_getword_conf(cmd->pool, &usernames);
    apr_table_t *usertable;

    /* Since we are a raw argument, it is possible for us to be called with
     * zero arguments.  So that we aren't ambiguous, flat out reject this.
     */
    if (*kw == '\0') {
        return "UserDir requires an argument.";
    }

    /*
     * Let's do the comparisons once.
     */
    if ((!strcasecmp(kw, "disable")) || (!strcasecmp(kw, "disabled"))) {
        /*
         * If there are no usernames specified, this is a global disable - we
         * need do no more at this point than record the fact.
         */
        if (strlen(usernames) == 0) {
            s_cfg->globally_disabled = O_DISABLE;
            return NULL;
        }
        usertable = s_cfg->disabled_users;
    }
    else if ((!strcasecmp(kw, "enable")) || (!strcasecmp(kw, "enabled"))) {
        if (strlen(usernames) == 0) {
            s_cfg->globally_disabled = O_ENABLE;
            return NULL;
        }
        usertable = s_cfg->enabled_users;
    }
    else {
        /*
         * If the first (only?) value isn't one of our keywords, just copy
         * the string to the userdir string.
         */
        s_cfg->userdir = apr_pstrdup(cmd->pool, arg);
        return NULL;
    }
    /*
     * Now we just take each word in turn from the command line and add it to
     * the appropriate table.
     */
    while (*usernames) {
        username = ap_getword_conf(cmd->pool, &usernames);
        apr_table_setn(usertable, username, kw);
    }
    return NULL;
}