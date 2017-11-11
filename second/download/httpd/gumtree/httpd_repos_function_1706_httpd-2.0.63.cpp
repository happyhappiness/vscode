static int check_user_access(request_rec *r)
{
    auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                 &auth_module);
    char *user = r->user;
    int m = r->method_number;
    int method_restricted = 0;
    register int x;
    const char *t, *w;
    apr_table_t *grpstatus;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs;

    /* BUG FIX: tadc, 11-Nov-1995.  If there is no "requires" directive, 
     * then any user will do.
     */
    if (!reqs_arr) {
        return OK;
    }
    reqs = (require_line *)reqs_arr->elts;

    if (conf->auth_grpfile) {
        grpstatus = groups_for_user(r, user, conf->auth_grpfile);
    }
    else {
        grpstatus = NULL;
    }

    for (x = 0; x < reqs_arr->nelts; x++) {

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        method_restricted = 1;

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);
        if (!strcmp(w, "valid-user")) {
            return OK;
        }
        if (!strcmp(w, "user")) {
            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                if (!strcmp(user, w)) {
                    return OK;
                }
            }
        }
        else if (!strcmp(w, "group")) {
            if (!grpstatus) {
                return DECLINED;        /* DBM group?  Something else? */
            }

            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                if (apr_table_get(grpstatus, w)) {
                    return OK;
                }
            }
        }
        else if (conf->auth_authoritative) {
            /* if we aren't authoritative, any require directive could be
             * valid even if we don't grok it.  However, if we are 
             * authoritative, we can warn the user they did something wrong.
             * That something could be a missing "AuthAuthoritative off", but
             * more likely is a typo in the require directive.
             */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "access to %s failed, reason: unknown require "
                          "directive:\"%s\"", r->uri, reqs[x].requirement);
        }
    }

    if (!method_restricted) {
        return OK;
    }

    if (!(conf->auth_authoritative)) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "access to %s failed, reason: user %s not allowed access",
                  r->uri, user);
        
    ap_note_basic_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}