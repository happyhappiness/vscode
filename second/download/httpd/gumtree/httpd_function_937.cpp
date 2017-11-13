static void process_resource_config_nofnmatch(server_rec *s, const char *fname,
                                              ap_directive_t **conftree,
                                              apr_pool_t *p,
                                              apr_pool_t *ptemp,
                                              unsigned depth)
{
    cmd_parms parms;
    ap_configfile_t *cfp;
    const char *errmsg;

    if (ap_is_directory(p, fname)) {
        apr_dir_t *dirp;
        apr_finfo_t dirent;
        int current;
        apr_array_header_t *candidates = NULL;
        fnames *fnew;
        apr_status_t rv;
        char errmsg[120], *path = apr_pstrdup(p, fname);

        if (++depth > AP_MAX_INCLUDE_DIR_DEPTH) {
            fprintf(stderr, "%s: Directory %s exceeds the maximum include "
                    "directory nesting level of %u. You have probably a "
                    "recursion somewhere.\n", ap_server_argv0, path,
                    AP_MAX_INCLUDE_DIR_DEPTH);
            exit(1);
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
                && strcmp(dirent.name, "..")) {
                fnew = (fnames *) apr_array_push(candidates);
                fnew->fname = ap_make_full_path(p, path, dirent.name);
            }
        }

        apr_dir_close(dirp);
        if (candidates->nelts != 0) {
            qsort((void *) candidates->elts, candidates->nelts,
                  sizeof(fnames), fname_alphasort);

            /*
             * Now recurse these... we handle errors and subdirectories
             * via the recursion, which is nice
             */
            for (current = 0; current < candidates->nelts; ++current) {
                fnew = &((fnames *) candidates->elts)[current];
                process_resource_config_nofnmatch(s, fnew->fname, conftree, p,
                                                  ptemp, depth);
            }
        }

        return;
    }

    /* GCC's initialization extensions are soooo nice here... */
    parms = default_parms;
    parms.pool = p;
    parms.temp_pool = ptemp;
    parms.server = s;
    parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);

    if (ap_pcfg_openfile(&cfp, p, fname) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: could not open document config file %s",
                     ap_server_argv0, fname);
        exit(1);
    }

    parms.config_file = cfp;

    errmsg = ap_build_config(&parms, p, ptemp, conftree);

    if (errmsg != NULL) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Syntax error on line %d of %s:",
                     parms.err_directive->line_num,
                     parms.err_directive->filename);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s", errmsg);
        exit(1);
    }

    ap_cfg_closefile(cfp);

    return;
}