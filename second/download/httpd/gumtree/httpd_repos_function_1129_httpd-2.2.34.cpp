static const char *add_action(cmd_parms *cmd, void *m_v,
                              const char *type, const char *script,
                              const char *option)
{
    action_dir_config *m = (action_dir_config *)m_v;

    if (option && strcasecmp(option, "virtual")) {
        return apr_pstrcat(cmd->pool,
                           "unrecognized option '", option, "'", NULL);
    }

    apr_table_setn(m->action_types, type,
                   apr_pstrcat(cmd->pool, option ? "1" : "0", script, NULL));
    m->configured = 1;

    return NULL;
}