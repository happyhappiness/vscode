                                            apr_pool_t *ptemp)
{
    cmd_parms parms;
    apr_finfo_t finfo;
    const char *errmsg;
    ap_configfile_t *cfp;

    /* don't require conf/httpd.conf if we have a -C or -c switch */
    if ((ap_server_pre_read_config->nelts
        || ap_server_post_read_config->nelts)
        && !(strcmp(fname, ap_server_root_relative(p, SERVER_CONFIG_FILE)))) {
        if (apr_lstat(&finfo, fname, APR_FINFO_TYPE, p) != APR_SUCCESS)
            return;
    }

    /*
     * here we want to check if the candidate file is really a
     * directory, and most definitely NOT a symlink (to prevent
     * horrible loops).  If so, let's recurse and toss it back
     * into the function.
     */
    if (ap_is_rdirectory(ptemp, fname)) {
        apr_dir_t *dirp;
        apr_finfo_t dirent;
        int current;
        apr_array_header_t *candidates = NULL;
        fnames *fnew;
        apr_status_t rv;
        char errmsg[120];

        /*
         * first course of business is to grok all the directory
         * entries here and store 'em away. Recall we need full pathnames
         * for this.
         */
        fprintf(stderr, "Processing config directory: %s\n", fname);
        rv = apr_dir_open(&dirp, fname, p);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "%s: could not open config directory %s: %s\n",
                    ap_server_argv0, fname,
                    apr_strerror(rv, errmsg, sizeof errmsg));
            exit(1);
        }

        candidates = apr_array_make(p, 1, sizeof(fnames));
        while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
            /* strip out '.' and '..' */
            if (strcmp(dirent.name, ".")
                && strcmp(dirent.name, "..")) {
                fnew = (fnames *) apr_array_push(candidates);
                fnew->fname = ap_make_full_path(p, fname, dirent.name);
            }
        }

        apr_dir_close(dirp);
        if (candidates->nelts != 0) {
            qsort((void *) candidates->elts, candidates->nelts,
