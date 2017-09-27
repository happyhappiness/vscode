static const authz_provider authz_method_provider =
{
    &method_check_authorization,
    &method_parse_config,
};

/*
 * expr authz provider
 */

#define REQUIRE_EXPR_NOTE "Require_expr_info"
struct require_expr_info {
    ap_expr_info_t *expr;
    int want_user;
};

static int expr_lookup_fn(ap_expr_lookup_parms *parms)
{
    if (parms->type == AP_EXPR_FUNC_VAR
        && strcasecmp(parms->name, "REMOTE_USER") == 0) {
        struct require_expr_info *info;
        apr_pool_userdata_get((void**)&info, REQUIRE_EXPR_NOTE, parms->ptemp);
        AP_DEBUG_ASSERT(info != NULL);
        info->want_user = 1;
    }
    return ap_expr_lookup_default(parms);
}

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

static const authz_provider authz_expr_provider =
{
    &expr_check_authorization,
    &expr_parse_config,
};

