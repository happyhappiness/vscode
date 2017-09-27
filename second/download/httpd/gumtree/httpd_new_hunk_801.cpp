    const fnames *f1 = fn1;
    const fnames *f2 = fn2;

    return strcmp(f1->fname,f2->fname);
}

static const char *process_resource_config_nofnmatch(server_rec *s,
                                                     const char *fname,
                                                     ap_directive_t **conftree,
                                                     apr_pool_t *p,
                                                     apr_pool_t *ptemp,
                                                     unsigned depth)
{
    cmd_parms parms;
    ap_configfile_t *cfp;
    const char *error;
    apr_status_t rv;

    if (ap_is_directory(p, fname)) {
        apr_dir_t *dirp;
        apr_finfo_t dirent;
        int current;
        apr_array_header_t *candidates = NULL;
        fnames *fnew;
        char *path = apr_pstrdup(p, fname);

        if (++depth > AP_MAX_INCLUDE_DIR_DEPTH) {
            return apr_psprintf(p, "Directory %s exceeds the maximum include "
                                "directory nesting level of %u. You have "
                                "probably a recursion somewhere.", path,
                                AP_MAX_INCLUDE_DIR_DEPTH);
        }

        /*
         * first course of business is to grok all the directory
         * entries here and store 'em away. Recall we need full pathnames
         * for this.
         */
        rv = apr_dir_open(&dirp, path, p);
        if (rv != APR_SUCCESS) {
            char errmsg[120];
            return apr_psprintf(p, "Could not open config directory %s: %s",
                                path, apr_strerror(rv, errmsg, sizeof errmsg));
        }

        candidates = apr_array_make(p, 1, sizeof(fnames));
        while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
            /* strip out '.' and '..' */
            if (strcmp(dirent.name, ".")
