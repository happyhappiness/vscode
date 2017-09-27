static const authz_provider authz_method_provider =
{
    &method_check_authorization,
    &method_parse_config,
};

static authz_status expr_check_authorization(request_rec *r,
                                             const char *require_line,
                                             const void *parsed_require_line)
{
    const char *err = NULL;
    const ap_expr_info_t *expr = parsed_require_line;
    int rc = ap_expr_exec(r, expr, &err);

    if (rc <= 0)
        /* XXX: real error handling? */
        return AUTHZ_DENIED;
    else
        return AUTHZ_GRANTED;
}

static const char *expr_parse_config(cmd_parms *cmd, const char *require_line,
                                     const void **parsed_require_line)
{
    const char *expr_err = NULL;
    ap_expr_info_t *expr = ap_expr_parse_cmd(cmd, require_line, 0, &expr_err,
                                             NULL);

    if (expr_err)
        return "Cannot parse expression in require line";

    *parsed_require_line = expr;

    return NULL;
}

static const authz_provider authz_expr_provider =
{
    &expr_check_authorization,
    &expr_parse_config,
};

