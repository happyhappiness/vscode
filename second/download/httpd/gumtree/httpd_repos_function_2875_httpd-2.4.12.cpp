static const char *expr_parse_config(cmd_parms *cmd, const char *require_line,
                                     const void **parsed_require_line)
{
    const char *expr_err = NULL;
    struct require_expr_info *info = apr_pcalloc(cmd->pool, sizeof(*info));

    apr_pool_userdata_setn(info, REQUIRE_EXPR_NOTE, apr_pool_cleanup_null,
                          cmd->temp_pool);
    info->expr = ap_expr_parse_cmd(cmd, require_line, 0, &expr_err,
                                   expr_lookup_fn);

    if (expr_err)
        return apr_pstrcat(cmd->temp_pool,
                           "Cannot parse expression in require line: ",
                           expr_err, NULL);

    *parsed_require_line = info;

    return NULL;
}