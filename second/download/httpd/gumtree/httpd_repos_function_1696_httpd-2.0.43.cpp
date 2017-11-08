static int dbm_check_auth(request_rec *r)
{
    dbm_auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                     &auth_dbm_module);
    char *user = r->user;
    int m = r->method_number;

    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs = reqs_arr ? (require_line *) reqs_arr->elts : NULL;

    register int x;
    const char *t;
    char *w;

    if (!conf->auth_dbmgrpfile)
        return DECLINED;
    if (!reqs_arr)
        return DECLINED;

    for (x = 0; x < reqs_arr->nelts; x++) {

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m)))
            continue;

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        if (!strcmp(w, "group") && conf->auth_dbmgrpfile) {
            const char *orig_groups, *groups;
            char *v;

            if (!(groups = get_dbm_grp(r, user, conf->auth_dbmgrpfile,
                                       conf->auth_dbmtype))) {
                if (!(conf->auth_dbmauthoritative))
                    return DECLINED;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "user %s not in DBM group file %s: %s",
                            user, conf->auth_dbmgrpfile, r->filename);
                ap_note_basic_auth_failure(r);
                return HTTP_UNAUTHORIZED;
            }
            orig_groups = groups;
            while (t[0]) {
                w = ap_getword_white(r->pool, &t);
                groups = orig_groups;
                while (groups[0]) {
                    v = ap_getword(r->pool, &groups, ',');
                    if (!strcmp(v, w))
                        return OK;
                }
            }
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "user %s not in right group: %s",
                          user, r->filename);
            ap_note_basic_auth_failure(r);
            return HTTP_UNAUTHORIZED;
        }
    }

    return DECLINED;
}