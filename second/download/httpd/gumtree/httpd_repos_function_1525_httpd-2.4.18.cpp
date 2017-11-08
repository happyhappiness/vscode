static const char *set_script(cmd_parms *cmd, void *m_v,
                              const char *method, const char *script)
{
    action_dir_config *m = (action_dir_config *)m_v;
    int methnum;
    if (cmd->pool == cmd->temp_pool) {
        /* In .htaccess, we can't globally register new methods. */
        methnum = ap_method_number_of(method);
    }
    else {
        /* ap_method_register recognizes already registered methods,
         * so don't bother to check its previous existence explicitely.
         */
        methnum = ap_method_register(cmd->pool, method);
    }

    if (methnum == M_TRACE) {
        return "TRACE not allowed for Script";
    }
    else if (methnum == M_INVALID) {
        return apr_pstrcat(cmd->pool, "Could not register method '", method,
                           "' for Script", NULL);
    }

    m->scripted[methnum] = script;
    m->configured = 1;

    return NULL;
}