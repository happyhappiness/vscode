static char *lookup_map(request_rec *r, char *name, char *key)
{
    rewrite_server_conf *conf;
    rewritemap_entry *s;
    char *value;
    apr_finfo_t st;
    apr_status_t rv;

    /* get map configuration */
    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
    s = apr_hash_get(conf->rewritemaps, name, APR_HASH_KEY_STRING);

    /* map doesn't exist */
    if (!s) {
        return NULL;
    }

    switch (s->type) {
    /*
     * Text file map (perhaps random)
     */
    case MAPTYPE_RND:
    case MAPTYPE_TXT:
        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "mod_rewrite: can't access text RewriteMap file %s",
                          s->checkfile);
            rewritelog((r, 1, NULL,
                        "can't open RewriteMap file, see error log"));
            return NULL;
        }

        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
        if (!value) {
            rewritelog((r, 6, NULL,
                        "cache lookup FAILED, forcing new map lookup"));

            value = lookup_map_txtfile(r, s->datafile, key);
            if (!value) {
                rewritelog((r, 5, NULL, "map lookup FAILED: map=%s[txt] key=%s",
                            name, key));
                set_cache_value(s->cachename, st.mtime, key, "");
                return NULL;
            }

            rewritelog((r, 5, NULL,"map lookup OK: map=%s[txt] key=%s -> val=%s",
                        name, key, value));
            set_cache_value(s->cachename, st.mtime, key, value);
        }
        else {
            rewritelog((r,5,NULL,"cache lookup OK: map=%s[txt] key=%s -> val=%s",
                        name, key, value));
        }

        if (s->type == MAPTYPE_RND && *value) {
            value = select_random_value_part(r, value);
            rewritelog((r, 5, NULL, "randomly chosen the subvalue `%s'",value));
        }

        return *value ? value : NULL;

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
        }
        if(rv != APR_SUCCESS) {
            rewritelog((r, 1, NULL,
                        "can't open DBM RewriteMap file, see error log"));
            return NULL;
        }

        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
        if (!value) {
            rewritelog((r, 6, NULL,
                        "cache lookup FAILED, forcing new map lookup"));

            value = lookup_map_dbmfile(r, s->datafile, s->dbmtype, key);
            if (!value) {
                rewritelog((r, 5, NULL, "map lookup FAILED: map=%s[dbm] key=%s",
                            name, key));
                set_cache_value(s->cachename, st.mtime, key, "");
                return NULL;
            }

            rewritelog((r, 5, NULL, "map lookup OK: map=%s[dbm] key=%s -> "
                        "val=%s", name, key, value));

            set_cache_value(s->cachename, st.mtime, key, value);
            return value;
        }

        rewritelog((r, 5, NULL, "cache lookup OK: map=%s[dbm] key=%s -> val=%s",
                    name, key, value));
        return *value ? value : NULL;

    /*
     * Program file map
     */
    case MAPTYPE_PRG:
        value = lookup_map_program(r, s->fpin, s->fpout, key);
        if (!value) {
            rewritelog((r, 5,NULL,"map lookup FAILED: map=%s key=%s", name,
                        key));
            return NULL;
        }

        rewritelog((r, 5, NULL, "map lookup OK: map=%s key=%s -> val=%s",
                    name, key, value));
        return value;

    /*
     * Internal Map
     */
    case MAPTYPE_INT:
        value = s->func(r, key);
        if (!value) {
            rewritelog((r, 5,NULL,"map lookup FAILED: map=%s key=%s", name,
                        key));
            return NULL;
        }

        rewritelog((r, 5, NULL, "map lookup OK: map=%s key=%s -> val=%s",
                    name, key, value));
        return value;
    }

    return NULL;
}