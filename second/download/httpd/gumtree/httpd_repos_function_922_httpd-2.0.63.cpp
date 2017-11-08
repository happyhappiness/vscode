static const char *set_script(cmd_parms *cmd, void *m_v,
                              const char *method, const char *script)
{
    action_dir_config *m = (action_dir_config *)m_v;    
    int methnum;

    methnum = ap_method_number_of(method);
    if (methnum == M_TRACE)
        return "TRACE not allowed for Script";
    else if (methnum == M_INVALID)
        return "Unknown method type for Script";
    else
        m->scripted[methnum] = script;

    m->configured = 1;
    return NULL;
}