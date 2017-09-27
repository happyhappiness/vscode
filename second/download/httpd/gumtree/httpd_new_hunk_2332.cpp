    case MAPTYPE_TXT:
        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_rewrite: can't access text RewriteMap file %s",
                          s->checkfile);
            return NULL;
        }

        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
        if (!value) {
            rewritelog((r, 6, NULL,
