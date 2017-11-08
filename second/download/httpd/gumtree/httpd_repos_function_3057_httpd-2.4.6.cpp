static const char *process_resource_config_fnmatch(server_rec *s,
                                                   const char *path,
                                                   const char *fname,
                                                   ap_directive_t **conftree,
                                                   apr_pool_t *p,
                                                   apr_pool_t *ptemp,
                                                   unsigned depth,
                                                   int optional)
{
    const char *rest;
    apr_status_t rv;
    apr_dir_t *dirp;
    apr_finfo_t dirent;
    apr_array_header_t *candidates = NULL;
    fnames *fnew;
    int current;

    /* find the first part of the filename */
    rest = ap_strchr_c(fname, '/');
    if (rest) {
        fname = apr_pstrndup(ptemp, fname, rest - fname);
        rest++;
    }

    /* optimisation - if the filename isn't a wildcard, process it directly */
    if (!apr_fnmatch_test(fname)) {
        path = ap_make_full_path(ptemp, path, fname);
        if (!rest) {
            return process_resource_config_nofnmatch(s, path,
                                                     conftree, p,
                                                     ptemp, 0, optional);
        }
        else {
            return process_resource_config_fnmatch(s, path, rest,
                                                   conftree, p,
                                                   ptemp, 0, optional);
        }
    }

    /*
     * first course of business is to grok all the directory
     * entries here and store 'em away. Recall we need full pathnames
     * for this.
     */
    rv = apr_dir_open(&dirp, path, ptemp);
    if (rv != APR_SUCCESS) {
        return apr_psprintf(p, "Could not open config directory %s: %pm",
                            path, &rv);
    }

    candidates = apr_array_make(ptemp, 1, sizeof(fnames));
    while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp) == APR_SUCCESS) {
        /* strip out '.' and '..' */
        if (strcmp(dirent.name, ".")
            && strcmp(dirent.name, "..")
            && (apr_fnmatch(fname, dirent.name,
                            APR_FNM_PERIOD) == APR_SUCCESS)) {
            const char *full_path = ap_make_full_path(ptemp, path, dirent.name);
            /* If matching internal to path, and we happen to match something
             * other than a directory, skip it
             */
            if (rest && (rv == APR_SUCCESS) && (dirent.filetype != APR_DIR)) {
                continue;
            }
            fnew = (fnames *) apr_array_push(candidates);
            fnew->fname = full_path;
        }
    }

    apr_dir_close(dirp);
    if (candidates->nelts != 0) {
        const char *error;

        qsort((void *) candidates->elts, candidates->nelts,
              sizeof(fnames), fname_alphasort);

        /*
         * Now recurse these... we handle errors and subdirectories
         * via the recursion, which is nice
         */
        for (current = 0; current < candidates->nelts; ++current) {
            fnew = &((fnames *) candidates->elts)[current];
            if (!rest) {
                error = process_resource_config_nofnmatch(s, fnew->fname,
                                                          conftree, p,
                                                          ptemp, 0, optional);
            }
            else {
                error = process_resource_config_fnmatch(s, fnew->fname, rest,
                                                        conftree, p,
                                                        ptemp, 0, optional);
            }
            if (error) {
                return error;
            }
        }
    }
    else {

        if (!optional) {
            return apr_psprintf(p, "No matches for the wildcard '%s' in '%s', failing "
                                   "(use IncludeOptional if required)", fname, path);
        }
    }

    return NULL;
}