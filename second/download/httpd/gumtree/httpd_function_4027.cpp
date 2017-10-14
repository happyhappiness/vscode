static int add_cern_meta_data(request_rec *r)
{
    char *metafilename;
    char *leading_slash;
    char *last_slash;
    char *real_file;
    char *scrap_book;
    apr_file_t *f = NULL;
    apr_status_t retcode;
    cern_meta_dir_config *dconf;
    int rv;
    request_rec *rr;

    dconf = ap_get_module_config(r->per_dir_config, &cern_meta_module);

    if (!dconf->metafiles) {
        return DECLINED;
    }

    /* if ./.web/$1.meta exists then output 'asis' */

    if (r->finfo.filetype == APR_NOFILE) {
        return DECLINED;
    }

    /* is this a directory? */
    if (r->finfo.filetype == APR_DIR || r->uri[strlen(r->uri) - 1] == '/') {
        return DECLINED;
    }

    /* what directory is this file in? */
    scrap_book = apr_pstrdup(r->pool, r->filename);

    leading_slash = strchr(scrap_book, '/');
    last_slash = strrchr(scrap_book, '/');
    if ((last_slash != NULL) && (last_slash != leading_slash)) {
        /* skip over last slash */
        real_file = last_slash;
        real_file++;
        *last_slash = '\0';
    }
    else {
        /* no last slash, buh?! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "internal error in mod_cern_meta: %s", r->filename);
        /* should really barf, but hey, let's be friends... */
        return DECLINED;
    }

    metafilename = apr_pstrcat(r->pool, scrap_book, "/",
               dconf->metadir ? dconf->metadir : DEFAULT_METADIR,
               "/", real_file,
         dconf->metasuffix ? dconf->metasuffix : DEFAULT_METASUFFIX,
               NULL);

    /* It sucks to require this subrequest to complete, because this
     * means people must leave their meta files accessible to the world.
     * A better solution might be a "safe open" feature of pfopen to avoid
     * pipes, symlinks, and crap like that.
     *
     * In fact, this doesn't suck.  Because <Location > blocks are never run
     * against sub_req_lookup_file, the meta can be somewhat protected by
     * either masking it with a <Location > directive or alias, or stowing
     * the file outside of the web document tree, while providing the
     * appropriate directory blocks to allow access to it as a file.
     */
    rr = ap_sub_req_lookup_file(metafilename, r, NULL);
    if (rr->status != HTTP_OK) {
    ap_destroy_sub_req(rr);
        return DECLINED;
    }
    ap_destroy_sub_req(rr);

    retcode = apr_file_open(&f, metafilename, APR_READ, APR_OS_DEFAULT, r->pool);
    if (retcode != APR_SUCCESS) {
        if (APR_STATUS_IS_ENOENT(retcode)) {
            return DECLINED;
        }
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "meta file permissions deny server access: %s", metafilename);
        return HTTP_FORBIDDEN;
    }

    /* read the headers in */
    rv = scan_meta_file(r, f);
    apr_file_close(f);

    return rv;
}