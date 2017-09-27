    case MAPTYPE_DBM:
        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_rewrite: can't access DBM RewriteMap file %s",
                          s->checkfile);
            rewritelog((r, 1, NULL,
                        "can't open DBM RewriteMap file, see error log"));
            return NULL;
        }

        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
