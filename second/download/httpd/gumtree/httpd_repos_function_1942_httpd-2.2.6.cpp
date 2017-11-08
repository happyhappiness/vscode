static int check_user_access(request_rec *r)
{
    authz_user_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &authz_user_module);
    char *user = r->user;
    int m = r->method_number;
    int required_user = 0;
    register int x;
    const char *t, *w;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs;

    /* BUG FIX: tadc, 11-Nov-1995.  If there is no "requires" directive,
     * then any user will do.
     */
    if (!reqs_arr) {
        return DECLINED;
    }
    reqs = (require_line *)reqs_arr->elts;

    for (x = 0; x < reqs_arr->nelts; x++) {

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);
        if (!strcasecmp(w, "valid-user")) {
            return OK;
        }
        if (!strcasecmp(w, "user")) {
            /* And note that there are applicable requirements
             * which we consider ourselves the owner of.
             */
            required_user = 1;
            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                if (!strcmp(user, w)) {
                    return OK;
                }
            }
        }
    }

    if (!required_user) {
        /* no applicable requirements */
        return DECLINED;
    }

    if (!conf->authoritative) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "access to %s failed, reason: user '%s' does not meet "
                  "'require'ments for user/valid-user to be allowed access",
                  r->uri, user);

    ap_note_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}