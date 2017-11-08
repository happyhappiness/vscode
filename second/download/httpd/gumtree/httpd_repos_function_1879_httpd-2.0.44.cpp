static const char *set_limit_req_fieldsize(cmd_parms *cmd, void *dummy,
                                           const char *arg)
{
    const char *err = ap_check_cmd_context(cmd,
                                           NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);
    int lim;

    if (err != NULL) {
        return err;
    }

    lim = atoi(arg);
    if (lim < 0) {
        return apr_pstrcat(cmd->temp_pool, "LimitRequestFieldsize \"", arg,
                          "\" must be a non-negative integer (0 = no limit)",
                          NULL);
    }

    if (lim > DEFAULT_LIMIT_REQUEST_FIELDSIZE) {
        return apr_psprintf(cmd->temp_pool, "LimitRequestFieldsize \"%s\" "
                           "must not exceed the precompiled maximum of %d",
                            arg, DEFAULT_LIMIT_REQUEST_FIELDSIZE);
    }

    cmd->server->limit_req_fieldsize = lim;
    return NULL;
}