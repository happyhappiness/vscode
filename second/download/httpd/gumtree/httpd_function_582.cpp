static apr_table_t *groups_for_user(request_rec *r, const char *user,
                                    const char *grpfile)
{
    ap_configfile_t *f;
    apr_table_t *grps = apr_table_make(r->pool, 15);
    apr_pool_t *sp;
    char l[MAX_STRING_LEN];
    const char *group_name, *ll, *w;
    apr_status_t sts;

    if ((sts = ap_pcfg_openfile(&f, r->pool, grpfile)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, sts, r,
                      "Digest: Could not open group file: %s", grpfile);
        return NULL;
    }

    if (apr_pool_create(&sp, r->pool) != APR_SUCCESS) {
        return NULL;
    }

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }
        ll = l;
        apr_pool_clear(sp);

        group_name = ap_getword(sp, &ll, ':');

        while (ll[0]) {
            w = ap_getword_conf(sp, &ll);
            if (!strcmp(w, user)) {
                apr_table_setn(grps, apr_pstrdup(r->pool, group_name), "in");
                break;
            }
        }
    }

    ap_cfg_closefile(f);
    apr_pool_destroy(sp);
    return grps;
}