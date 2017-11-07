static authz_status expr_check_authorization(request_rec *r,
                                             const char *require_line,
                                             const void *parsed_require_line)
{
    const char *err = NULL;
    const struct require_expr_info *info = parsed_require_line;
    int rc = ap_expr_exec(r, info->expr, &err);

    if (rc < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02320)
                      "Error evaluating expression in 'Require expr': %s",
                      err);
        return AUTHZ_GENERAL_ERROR;
    }
    else if (rc == 0) {
        if (info->want_user)
            return AUTHZ_DENIED_NO_USER;
        else
            return AUTHZ_DENIED;
    }
    else {
        return AUTHZ_GRANTED;
    }
}