static const char *include_config (cmd_parms *cmd, void *dummy,
                                   const char *name)
{
    ap_directive_t *conftree = NULL;
    const char* conffile, *error;
    unsigned *recursion;
    void *data;

    apr_pool_userdata_get(&data, "ap_include_sentinel", cmd->pool);
    if (data) {
        recursion = data;
    }
    else {
        data = recursion = apr_palloc(cmd->pool, sizeof(*recursion));
        *recursion = 0;
        apr_pool_userdata_setn(data, "ap_include_sentinel", NULL, cmd->pool);
    }

    if (++*recursion > AP_MAX_INCLUDE_DEPTH) {
        *recursion = 0;
        return apr_psprintf(cmd->pool, "Exceeded maximum include depth of %u. "
                            "You have probably a recursion somewhere.",
                            AP_MAX_INCLUDE_DEPTH);
    }

    conffile = ap_server_root_relative(cmd->pool, name);
    if (!conffile) {
        *recursion = 0;
        return apr_pstrcat(cmd->pool, "Invalid Include path ",
                           name, NULL);
    }

    error = ap_process_resource_config(cmd->server, conffile,
                                       &conftree, cmd->pool, cmd->temp_pool);
    if (error) {
        *recursion = 0;
        return error;
    }

    *(ap_directive_t **)dummy = conftree;

    /* recursion level done */
    if (*recursion) {
        --*recursion;
    }

    return NULL;
}