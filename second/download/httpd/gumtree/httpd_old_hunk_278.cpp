    entries = (rewritemap_entry *)rewritemaps->elts;
    for (i = 0; i < rewritemaps->nelts; i++) {
        s = &entries[i];
        if (strcmp(s->name, name) == 0) {
            if (s->type == MAPTYPE_TXT) {
                if (stat(s->checkfile, &st) == -1) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                                 "mod_rewrite: can't access text RewriteMap "
                                 "file %s", s->checkfile);
                    rewritelog(r, 1, "can't open RewriteMap file, "
                               "see error log");
                    return NULL;
                }
