static int digest_check_auth(request_rec *r)
{
    const digest_config_rec *conf =
                (digest_config_rec *) ap_get_module_config(r->per_dir_config,
                                                           &auth_digest_module);
    const char *user = r->user;
    int m = r->method_number;
    int method_restricted = 0;
    register int x;
    const char *t, *w;
    apr_table_t *grpstatus;
    const apr_array_header_t *reqs_arr;
    require_line *reqs;

    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Digest")) {
        return DECLINED;
    }

    reqs_arr = ap_requires(r);
    /* If there is no "requires" directive, then any user will do.
     */
    if (!reqs_arr) {
        return OK;
    }
    reqs = (require_line *) reqs_arr->elts;

    if (conf->grpfile) {
        grpstatus = groups_for_user(r, user, conf->grpfile);
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
        if (!strcasecmp(w, "valid-user")) {
            return OK;
        }
        else if (!strcasecmp(w, "user")) {
            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                if (!strcmp(user, w)) {
                    return OK;
                }
            }
        }
        else if (!strcasecmp(w, "group")) {
            if (!grpstatus) {
                return DECLINED;
            }

            while (t[0]) {
                w = ap_getword_conf(r->pool, &t);
                if (apr_table_get(grpstatus, w)) {
                    return OK;
                }
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: access to %s failed, reason: unknown "
                          "require directive \"%s\"",
                          r->uri, reqs[x].requirement);
            return DECLINED;
        }
    }

    if (!method_restricted) {
        return OK;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Digest: access to %s failed, reason: user %s not "
                  "allowed access", r->uri, user);

    note_digest_auth_failure(r, conf,
        (digest_header_rec *) ap_get_module_config(r->request_config,
                                                   &auth_digest_module),
        0);
    return HTTP_UNAUTHORIZED;
}