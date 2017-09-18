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
