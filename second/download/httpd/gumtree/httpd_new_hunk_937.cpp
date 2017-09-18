
    entries = (rewritemap_entry *)rewritemaps->elts;
    for (i = 0; i < rewritemaps->nelts; i++) {
        s = &entries[i];
        if (strcmp(s->name, name) == 0) {
            if (s->type == MAPTYPE_TXT) {
                if ((rv = apr_stat(&st, s->checkfile,
                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "mod_rewrite: can't access text RewriteMap "
                                  "file %s", s->checkfile);
                    rewritelog(r, 1, "can't open RewriteMap file, "
                               "see error log");
                    return NULL;
                }
                value = get_cache_string(cachep, s->name, CACHEMODE_TS,
                                         st.mtime, key);
