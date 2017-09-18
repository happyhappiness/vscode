                    return value;
                }
            }
            else if (s->type == MAPTYPE_DBM) {
#ifndef NO_DBM_REWRITEMAP
                if (stat(s->checkfile, &st) == -1) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                                 "mod_rewrite: can't access DBM RewriteMap "
                                 "file %s", s->checkfile);
                    rewritelog(r, 1, "can't open DBM RewriteMap file, "
                               "see error log");
                    return NULL;
                }
