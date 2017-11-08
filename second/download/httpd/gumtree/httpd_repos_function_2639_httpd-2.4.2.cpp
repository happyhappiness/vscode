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