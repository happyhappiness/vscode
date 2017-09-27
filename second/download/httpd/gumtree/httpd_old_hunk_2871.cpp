    /*
     * DBM file map
     */
    case MAPTYPE_DBM:
        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_rewrite: can't access DBM RewriteMap file %s",
                          s->checkfile);
        }
        else if(s->checkfile2 != NULL) {
            apr_finfo_t st2;

            rv = apr_stat(&st2, s->checkfile2, APR_FINFO_MIN, r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "mod_rewrite: can't access DBM RewriteMap "
                              "file %s", s->checkfile2);
            }
            else if(st2.mtime > st.mtime) {
                st.mtime = st2.mtime;
            }
