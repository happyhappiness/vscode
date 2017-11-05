static int check_user_access(request_rec *r)
{
    authz_groupfile_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &authz_groupfile_module);
    char *user = r->user;
    int m = r->method_number;
    int required_group = 0;
    register int x;
    const char *t, *w;
    apr_table_t *grpstatus = NULL;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs;
    const char *filegroup = NULL;
    char *reason = NULL;

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
        return DECLINED;
    }

    if (!reqs_arr) {
        return DECLINED; /* XXX change from legacy */
    }

    /* If there's no user, it's a misconfiguration */
    if (!user) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    reqs = (require_line *)reqs_arr->elts;

    for (x = 0; x < reqs_arr->nelts; x++) {

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        /* needs mod_authz_owner to be present */
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
            required_group = 1; /* remember the requirement */

            /* create group table only if actually needed. */
            if (!grpstatus) {
                apr_status_t status;

                status = groups_for_user(r->pool, user, conf->groupfile,
                                         &grpstatus);

                if (status != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                                  "Could not open group file: %s",
                                  conf->groupfile);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                if (apr_table_elts(grpstatus)->nelts == 0) {
                    /* no groups available, so exit immediately */
                    reason = apr_psprintf(r->pool,
                                          "user doesn't appear in group file "
                                          "(%s).", conf->groupfile);
                    break;
                }
            }

            if (filegroup) {
                if (apr_table_get(grpstatus, filegroup)) {
                    return OK;
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
                    w = ap_getword_conf(r->pool, &t);
                    if (apr_table_get(grpstatus, w)) {
                        return OK;
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