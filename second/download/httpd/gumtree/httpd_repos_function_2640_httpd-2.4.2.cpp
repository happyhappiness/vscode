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