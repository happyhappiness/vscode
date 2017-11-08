static struct ent *make_autoindex_entry(const apr_finfo_t *dirent,
                                        int autoindex_opts,
                                        autoindex_config_rec *d,
                                        request_rec *r, char keyid,
                                        char direction,
                                        const char *pattern)
{
    request_rec *rr;
    struct ent *p;
    int show_forbidden = 0;

    /* Dot is ignored, Parent is handled by make_parent_entry() */
    if ((dirent->name[0] == '.') && (!dirent->name[1]
        || ((dirent->name[1] == '.') && !dirent->name[2])))
        return (NULL);

    /*
     * On some platforms, the match must be case-blind.  This is really
     * a factor of the filesystem involved, but we can't detect that
     * reliably - so we have to granularise at the OS level.
     */
    if (pattern && (apr_fnmatch(pattern, dirent->name,
                                APR_FNM_NOESCAPE | APR_FNM_PERIOD
#ifdef CASE_BLIND_FILESYSTEM
                                | APR_FNM_CASE_BLIND
#endif
                                )
                    != APR_SUCCESS)) {
        return (NULL);
    }

    if (ignore_entry(d, ap_make_full_path(r->pool,
                                          r->filename, dirent->name))) {
        return (NULL);
    }

    if (!(rr = ap_sub_req_lookup_dirent(dirent, r, AP_SUBREQ_NO_ARGS, NULL))) {
        return (NULL);
    }

    if ((autoindex_opts & SHOW_FORBIDDEN)
        && (rr->status == HTTP_UNAUTHORIZED || rr->status == HTTP_FORBIDDEN)) {
        show_forbidden = 1;
    }

    if ((rr->finfo.filetype != APR_DIR && rr->finfo.filetype != APR_REG)
        || !(rr->status == OK || ap_is_HTTP_SUCCESS(rr->status)
                              || ap_is_HTTP_REDIRECT(rr->status)
                              || show_forbidden == 1)) {
        ap_destroy_sub_req(rr);
        return (NULL);
    }

    p = (struct ent *) apr_pcalloc(r->pool, sizeof(struct ent));
    if (dirent->filetype == APR_DIR) {
        p->name = apr_pstrcat(r->pool, dirent->name, "/", NULL);
    }
    else {
        p->name = apr_pstrdup(r->pool, dirent->name);
    }
    p->size = -1;
    p->icon = NULL;
    p->alt = NULL;
    p->desc = NULL;
    p->lm = -1;
    p->isdir = 0;
    p->key = apr_toupper(keyid);
    p->ascending = (apr_toupper(direction) == D_ASCENDING);
    p->version_sort = !!(autoindex_opts & VERSION_SORT);
    p->ignore_case = !!(autoindex_opts & IGNORE_CASE);

    if (autoindex_opts & (FANCY_INDEXING | TABLE_INDEXING)) {
        p->lm = rr->finfo.mtime;
        if (dirent->filetype == APR_DIR) {
            if (autoindex_opts & FOLDERS_FIRST) {
                p->isdir = 1;
            }
            rr->filename = ap_make_dirstr_parent (rr->pool, rr->filename);

            /* omit the trailing slash (1.3 compat) */
            rr->filename[strlen(rr->filename) - 1] = '\0';

            if (!(p->icon = find_icon(d, rr, 1))) {
                p->icon = find_default_icon(d, "^^DIRECTORY^^");
            }
            if (!(p->alt = find_alt(d, rr, 1))) {
                if (!(p->alt = find_default_alt(d, "^^DIRECTORY^^"))) {
                    p->alt = "DIR";
                }
            }
        }
        else {
            p->icon = find_icon(d, rr, 0);
            p->alt = find_alt(d, rr, 0);
            p->size = rr->finfo.size;
        }

        p->desc = find_desc(d, rr->filename);

        if ((!p->desc) && (autoindex_opts & SCAN_HTML_TITLES)) {
            p->desc = apr_pstrdup(r->pool, find_title(rr));
        }
    }
    ap_destroy_sub_req(rr);
    /*
     * We don't need to take any special action for the file size key.
     * If we did, it would go here.
     */
    if (keyid == K_LAST_MOD) {
        if (p->lm < 0) {
            p->lm = 0;
        }
    }
    return (p);
}