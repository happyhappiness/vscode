static const char *set_limit_req_line(cmd_parms *cmd, void *dummy,
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
        return apr_pstrcat(cmd->temp_pool, "LimitRequestLine \"", arg,
                           "\" must be a non-negative integer", NULL);
    }

    if (lim > DEFAULT_LIMIT_REQUEST_LINE) {
        return apr_psprintf(cmd->temp_pool, "LimitRequestLine \"%s\" "
                            "must not exceed the precompiled maximum of %d",
                            arg, DEFAULT_LIMIT_REQUEST_LINE);
    }

    cmd->server->limit_req_line = lim;
    return NULL;
}