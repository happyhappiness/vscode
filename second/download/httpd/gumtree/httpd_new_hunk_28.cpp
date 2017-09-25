                                            apr_pool_t *ptemp)
{
    cmd_parms parms;
    apr_finfo_t finfo;
    const char *errmsg;
    ap_configfile_t *cfp;
    int ispatt;

    /* don't require conf/httpd.conf if we have a -C or -c switch */
    if ((ap_server_pre_read_config->nelts
        || ap_server_post_read_config->nelts)
        && !(strcmp(fname, ap_server_root_relative(p, SERVER_CONFIG_FILE)))) {
        if (apr_lstat(&finfo, fname, APR_FINFO_TYPE, p) != APR_SUCCESS)
            return;
    }

    ispatt = apr_fnmatch_test(fname);
    if (ispatt || ap_is_rdirectory(p, fname)) {
        apr_dir_t *dirp;
        apr_finfo_t dirent;
        int current;
        apr_array_header_t *candidates = NULL;
        fnames *fnew;
        apr_status_t rv;
        char errmsg[120], *path = apr_pstrdup(p, fname), *pattern = NULL;

        if (ispatt) {
            pattern = ap_strrchr(path, '/');
        
            AP_DEBUG_ASSERT(pattern != NULL); /* path must be absolute. */
        
            *pattern++ = '\0';
            
            if (apr_fnmatch_test(path)) {
                fprintf(stderr, "%s: wildcard patterns not allowed in Include "
                        "%s\n", ap_server_argv0, fname);
                exit(1);
            }

            if (!ap_is_rdirectory(p, path)){ 
                fprintf(stderr, "%s: Include directory '%s' not found",
                        ap_server_argv0, path);
                exit(1);
            }
            
            if (!apr_fnmatch_test(pattern)) {
                fprintf(stderr, "%s: must include a wildcard pattern "
                        "for Include %s\n", ap_server_argv0, fname);
                exit(1);
            }

        }

        /*
         * first course of business is to grok all the directory
         * entries here and store 'em away. Recall we need full pathnames
         * for this.
         */
        rv = apr_dir_open(&dirp, path, p);
        if (rv != APR_SUCCESS) {
            fprintf(stderr, "%s: could not open config directory %s: %s\n",
                    ap_server_argv0, path,
                    apr_strerror(rv, errmsg, sizeof errmsg));
            exit(1);
        }

        candidates = apr_array_make(p, 1, sizeof(fnames));
        while (apr_dir_read(&dirent, APR_FINFO_DIRENT, dirp) == APR_SUCCESS) {
            /* strip out '.' and '..' */
            if (strcmp(dirent.name, ".")
                && strcmp(dirent.name, "..")
                && (!ispatt ||
                    apr_fnmatch(pattern, dirent.name, 
                                FNM_PERIOD) == APR_SUCCESS)) {
                fnew = (fnames *) apr_array_push(candidates);
                fnew->fname = ap_make_full_path(p, path, dirent.name);
            }
        }

        apr_dir_close(dirp);
        if (candidates->nelts != 0) {
            qsort((void *) candidates->elts, candidates->nelts,
