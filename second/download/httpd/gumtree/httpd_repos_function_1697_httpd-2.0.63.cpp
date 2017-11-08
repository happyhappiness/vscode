static const char *anon_set_string_slots(cmd_parms *cmd,
                                         void *my_config, const char *arg)
{
    anon_auth_config_rec *conf = my_config;
    anon_auth *first;

    if (!(*arg))
        return "Anonymous string cannot be empty, use Anonymous_NoUserId instead";

    /* squeeze in a record */
    first = conf->anon_auth_passwords;

    if (!(conf->anon_auth_passwords = apr_palloc(cmd->pool, sizeof(anon_auth))) ||
       !(conf->anon_auth_passwords->password = apr_pstrdup(cmd->pool, arg)))
             return "Failed to claim memory for an anonymous password...";

    /* and repair the next */
    conf->anon_auth_passwords->next = first;

    return NULL;
}