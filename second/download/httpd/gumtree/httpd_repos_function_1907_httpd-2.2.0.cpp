static const char *anon_set_string_slots(cmd_parms *cmd,
                                         void *my_config, const char *arg)
{
    authn_anon_config_rec *conf = my_config;
    anon_auth_user *first;

    if (!*arg) {
        return "Anonymous string cannot be empty, use Anonymous_NoUserId";
    }

    /* squeeze in a record */
    if (!conf->anyuserid) {
        if (!strcmp(arg, "*")) {
            conf->anyuserid = 1;
        }
        else {
            first = conf->users;
            conf->users = apr_palloc(cmd->pool, sizeof(*conf->users));
            conf->users->user = apr_pstrdup(cmd->pool, arg);
            conf->users->next = first;
        }
    }

    return NULL;
}