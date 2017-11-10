static int check_file_owner(request_rec *r)
{
    authz_owner_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                        &authz_owner_module);
    int m = r->method_number;
    register int x;
    const char *t, *w;
    const apr_array_header_t *reqs_arr = ap_requires(r);
    require_line *reqs;
    int required_owner = 0;
    apr_status_t status = 0;
    char *reason = NULL;

    if (!reqs_arr) {
        return DECLINED;
    }

    reqs = (require_line *)reqs_arr->elts;
    for (x = 0; x < reqs_arr->nelts; x++) {

        /* if authoritative = On then break if a require already failed. */
        if (reason && conf->authoritative) {
            break;
        }

        if (!(reqs[x].method_mask & (AP_METHOD_BIT << m))) {
            continue;
        }

        t = reqs[x].requirement;
        w = ap_getword_white(r->pool, &t);

        if (!strcmp(w, "file-owner")) {
#if !APR_HAS_USER
            if ((required_owner & ~1) && conf->authoritative) {
                break;
            }

            required_owner |= 1; /* remember the requirement */
            reason = "'Require file-owner' is not supported on this platform.";
            continue;
#else  /* APR_HAS_USER */
            char *owner = NULL;
            apr_finfo_t finfo;

            if ((required_owner & ~1) && conf->authoritative) {
                break;
            }

            required_owner |= 1; /* remember the requirement */

            if (!r->filename) {
                reason = "no filename available";
                continue;
            }

            status = apr_stat(&finfo, r->filename, APR_FINFO_USER, r->pool);
            if (status != APR_SUCCESS) {
                reason = apr_pstrcat(r->pool, "could not stat file ",
                                     r->filename, NULL);
                continue;
            }

            if (!(finfo.valid & APR_FINFO_USER)) {
                reason = "no file owner information available";
                continue;
            }

            status = apr_uid_name_get(&owner, finfo.user, r->pool);
            if (status != APR_SUCCESS || !owner) {
                reason = "could not get name of file owner";
                continue;
            }

            if (strcmp(owner, r->user)) {
                reason = apr_psprintf(r->pool, "file owner %s does not match.",
                                      owner);
                continue;
            }

            /* this user is authorized */
            return OK;
#endif /* APR_HAS_USER */
        }

        /* file-group only figures out the file's group and lets
         * other modules do the actual authorization (against a group file/db).
         * Thus, these modules have to hook themselves after
         * mod_authz_owner and of course recognize 'file-group', too.
         */
        if (!strcmp(w, "file-group")) {
#if !APR_HAS_USER
            if ((required_owner & ~6) && conf->authoritative) {
                break;
            }

            required_owner |= 2; /* remember the requirement */
            reason = "'Require file-group' is not supported on this platform.";
            continue;
#else  /* APR_HAS_USER */
            char *group = NULL;
            apr_finfo_t finfo;

            if ((required_owner & ~6) && conf->authoritative) {
                break;
            }

            required_owner |= 2; /* remember the requirement */

            if (!r->filename) {
                reason = "no filename available";
                continue;
            }

            status = apr_stat(&finfo, r->filename, APR_FINFO_GROUP, r->pool);
            if (status != APR_SUCCESS) {
                reason = apr_pstrcat(r->pool, "could not stat file ",
                                     r->filename, NULL);
                continue;
            }

            if (!(finfo.valid & APR_FINFO_GROUP)) {
                reason = "no file group information available";
                continue;
            }

            status = apr_gid_name_get(&group, finfo.group, r->pool);
            if (status != APR_SUCCESS || !group) {
                reason = "could not get name of file group";
                continue;
            }

            /* store group name in a note and let others decide... */
            apr_table_setn(r->notes, AUTHZ_GROUP_NOTE, group);
            required_owner |= 4;
            continue;
#endif /* APR_HAS_USER */
        }
    }

    if (!required_owner || !conf->authoritative) {
        return DECLINED;
    }

    /* allow file-group passed to group db modules either if this is the
     * only applicable requirement here or if a file-owner failed but we're
     * not authoritative.
     * This allows configurations like:
     *
     * AuthzOwnerAuthoritative Off
     * require file-owner
     * require file-group
     *
     * with the semantical meaning of "either owner or group must match"
     * (inclusive or)
     *
     * [ 6 == 2 | 4; 7 == 1 | 2 | 4 ] should I use #defines instead?
     */
    if (required_owner == 6 || (required_owner == 7 && !conf->authoritative)) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                  "Authorization of user %s to access %s failed, reason: %s",
                  r->user, r->uri, reason ? reason : "unknown");

    ap_note_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}