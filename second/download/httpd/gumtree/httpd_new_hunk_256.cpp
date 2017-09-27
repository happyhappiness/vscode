    const fnames *f1 = fn1;
    const fnames *f2 = fn2;

    return strcmp(f1->fname,f2->fname);
}

static void process_resource_config_nofnmatch(server_rec *s, const char *fname,
                                              ap_directive_t **conftree,
                                              apr_pool_t *p,
                                              apr_pool_t *ptemp)
{
    cmd_parms parms;
    ap_configfile_t *cfp;
    const char *errmsg;

    if (ap_is_rdirectory(p, fname)) {
        apr_dir_t *dirp;
        apr_finfo_t dirent;
        int current;
        apr_array_header_t *candidates = NULL;
        fnames *fnew;
        apr_status_t rv;
        char errmsg[120], *path = apr_pstrdup(p, fname);

        /*
         * first course of business is to grok all the directory
         * entries here and store 'em away. Recall we need full pathnames
         * for this.
         */
