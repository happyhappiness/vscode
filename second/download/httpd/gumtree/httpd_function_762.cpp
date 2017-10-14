static char *lookup_map(request_rec *r, char *name, char *key)
{
    rewrite_server_conf *conf;
    apr_array_header_t *rewritemaps;
    rewritemap_entry *entries;
    rewritemap_entry *s;
    char *value;
    apr_finfo_t st;
    apr_status_t rv;
    int i;

    /* get map configuration */
    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
    rewritemaps = conf->rewritemaps;

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
                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key);
                if (value == NULL) {
                    rewritelog(r, 6, "cache lookup FAILED, forcing new "
                               "map lookup");
                    if ((value =
                         lookup_map_txtfile(r, s->datafile, key)) != NULL) {
                        rewritelog(r, 5, "map lookup OK: map=%s key=%s[txt] "
                                   "-> val=%s", s->name, key, value);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, value);
                        return value;
                    }
                    else {
                        rewritelog(r, 5, "map lookup FAILED: map=%s[txt] "
                                   "key=%s", s->name, key);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, "");
                        return NULL;
                    }
                }
                else {
                    rewritelog(r, 5, "cache lookup OK: map=%s[txt] key=%s "
                               "-> val=%s", s->name, key, value);
                    return value[0] != '\0' ? value : NULL;
                }
            }
            else if (s->type == MAPTYPE_DBM) {
                if ((rv = apr_stat(&st, s->checkfile,
                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "mod_rewrite: can't access DBM RewriteMap "
                                  "file %s", s->checkfile);
                    rewritelog(r, 1, "can't open DBM RewriteMap file, "
                               "see error log");
                    return NULL;
                }
                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key);
                if (value == NULL) {
                    rewritelog(r, 6,
                               "cache lookup FAILED, forcing new map lookup");
                    if ((value =
                         lookup_map_dbmfile(r, s->datafile, s->dbmtype, key)) != NULL) {
                        rewritelog(r, 5, "map lookup OK: map=%s[dbm] key=%s "
                                   "-> val=%s", s->name, key, value);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, value);
                        return value;
                    }
                    else {
                        rewritelog(r, 5, "map lookup FAILED: map=%s[dbm] "
                                   "key=%s", s->name, key);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, "");
                        return NULL;
                    }
                }
                else {
                    rewritelog(r, 5, "cache lookup OK: map=%s[dbm] key=%s "
                               "-> val=%s", s->name, key, value);
                    return value[0] != '\0' ? value : NULL;
                }
            }
            else if (s->type == MAPTYPE_PRG) {
                if ((value =
                     lookup_map_program(r, s->fpin, s->fpout, key)) != NULL) {
                    rewritelog(r, 5, "map lookup OK: map=%s key=%s -> val=%s",
                               s->name, key, value);
                    return value;
                }
                else {
                    rewritelog(r, 5, "map lookup FAILED: map=%s key=%s",
                               s->name, key);
                }
            }
            else if (s->type == MAPTYPE_INT) {
                if ((value = s->func(r, key)) != NULL) {
                    rewritelog(r, 5, "map lookup OK: map=%s key=%s -> val=%s",
                               s->name, key, value);
                    return value;
                }
                else {
                    rewritelog(r, 5, "map lookup FAILED: map=%s key=%s",
                               s->name, key);
                }
            }
            else if (s->type == MAPTYPE_RND) {
                if ((rv = apr_stat(&st, s->checkfile,
                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "mod_rewrite: can't access text RewriteMap "
                                  "file %s", s->checkfile);
                    rewritelog(r, 1, "can't open RewriteMap file, "
                               "see error log");
                    return NULL;
                }
                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key);
                if (value == NULL) {
                    rewritelog(r, 6, "cache lookup FAILED, forcing new "
                               "map lookup");
                    if ((value =
                         lookup_map_txtfile(r, s->datafile, key)) != NULL) {
                        rewritelog(r, 5, "map lookup OK: map=%s key=%s[txt] "
                                   "-> val=%s", s->name, key, value);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, value);
                    }
                    else {
                        rewritelog(r, 5, "map lookup FAILED: map=%s[txt] "
                                   "key=%s", s->name, key);
                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
                                         st.mtime, key, "");
                        return NULL;
                    }
                }
                else {
                    rewritelog(r, 5, "cache lookup OK: map=%s[txt] key=%s "
                               "-> val=%s", s->name, key, value);
                }
                if (value[0] != '\0') {
                   value = select_random_value_part(r, value);
                   rewritelog(r, 5, "randomly choosen the subvalue `%s'",
                              value);
                }
                else {
                    value = NULL;
                }
                return value;
            }
        }
    }
    return NULL;
}