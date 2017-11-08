static int check_user_access(request_rec *r)
{
    authz_default_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                 &authz_default_module);
    int m = r->method_number;
    int method_restricted = 0;
    register int x;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs;

    /* BUG FIX: tadc, 11-Nov-1995.  If there is no "requires" directive,
     * then any user will do.
     */
    if (!reqs_arr) {
        return OK;
    }
    reqs = (require_line *)reqs_arr->elts;

    for (x = 0; x < reqs_arr->nelts; x++) {
        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }
        method_restricted = 1;
        break;
    }

    if (method_restricted == 0) {
        return OK;
    }

    if (!(conf->authoritative)) {
        return DECLINED;
    }

    /* if we aren't authoritative, any require directive could be
     * considered valid even if noone groked it.  However, if we are
     * authoritative, we can warn the user they did something wrong.
     *
     * That something could be a missing "AuthAuthoritative off", but
     * more likely is a typo in the require directive.
     */
    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "access to %s failed, reason: require directives "
                          "present and no Authoritative handler.", r->uri);

    ap_note_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}