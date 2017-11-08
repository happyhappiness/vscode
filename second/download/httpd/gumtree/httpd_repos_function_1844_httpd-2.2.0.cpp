static int dbm_check_auth(request_rec *r)
{
    authz_dbm_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authz_dbm_module);
    char *user = r->user;
    int m = r->method_number;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs = reqs_arr ? (require_line *) reqs_arr->elts : NULL;
    register int x;
    const char *t;
    char *w;
    int required_group = 0;
    const char *filegroup = NULL;
    const char *orig_groups = NULL;
    char *reason = NULL;

    if (!conf->grpfile) {
        return DECLINED;
    }

    if (!reqs_arr) {
        return DECLINED;
    }

    for (x = 0; x < reqs_arr->nelts; x++) {

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        if (!strcasecmp(w, "file-group")) {
            filegroup = apr_table_get(r->notes, AUTHZ_GROUP_NOTE);

            if (!filegroup) {
                /* mod_authz_owner is not present or not
                 * authoritative. We are just a helper module for testing
                 * group membership, so we don't care and decline.
                 */
                continue;
            }
        }

        if (!strcasecmp(w, "group") || filegroup) {
            const char *realm = ap_auth_name(r);
            const char *groups;
            char *v;

            /* remember that actually a group is required */
            required_group = 1;

            /* fetch group data from dbm file only once. */
            if (!orig_groups) {
                apr_status_t status;

                status = get_dbm_grp(r, apr_pstrcat(r->pool, user, ":", realm,
                                                    NULL),
                                     user,
                                     conf->grpfile, conf->dbmtype, &groups);

                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                                  "could not open dbm (type %s) group access "
                                  "file: %s", conf->dbmtype, conf->grpfile);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                if (groups == NULL) {
                    /* no groups available, so exit immediately */
                    reason = apr_psprintf(r->pool,
                                          "user doesn't appear in DBM group "
                                          "file (%s).", conf->grpfile);
                    break;
                }

                orig_groups = groups;
            }

            if (filegroup) {
                groups = orig_groups;
                while (groups[0]) {
                    v = ap_getword(r->pool, &groups, ',');
                    if (!strcmp(v, filegroup)) {
                        return OK;
                    }
                }

                if (conf->authoritative) {
                    reason = apr_psprintf(r->pool,
                                          "file group '%s' does not match.",
                                          filegroup);
                    break;
                }

                /* now forget the filegroup, thus alternatively require'd
                   groups get a real chance */
                filegroup = NULL;
            }
            else {
                while (t[0]) {
                    w = ap_getword_white(r->pool, &t);
                    groups = orig_groups;
                    while (groups[0]) {
                        v = ap_getword(r->pool, &groups, ',');
                        if (!strcmp(v, w)) {
                            return OK;
                        }
                    }
                }
            }
        }
    }

    /* No applicable "require group" for this method seen */
    if (!required_group || !conf->authoritative) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Authorization of user %s to access %s failed, reason: %s",
                  r->user, r->uri,
                  reason ? reason : "user is not part of the "
                                    "'require'ed group(s).");

    ap_note_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}