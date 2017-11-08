static const char *add_action(cmd_parms *cmd, void *m_v, 
                              const char *type, const char *script)
{
    action_dir_config *m = (action_dir_config *)m_v;
    apr_table_setn(m->action_types, type, script);
    m->configured = 1;
    return NULL;
}