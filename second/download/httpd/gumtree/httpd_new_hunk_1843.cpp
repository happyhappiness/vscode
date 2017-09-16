                    rewritelog(r, 5, "map lookup FAILED: map=%s key=%s",

                               s->name, key);

                }

            }

            else if (s->type == MAPTYPE_RND) {

                if (stat(s->checkfile, &st) == -1) {

                    ap_log_rerror(APLOG_MARK, APLOG_ERR, r,

                                 "mod_rewrite: can't access text RewriteMap "

                                 "file %s", s->checkfile);

                    rewritelog(r, 1, "can't open RewriteMap file, "

                               "see error log");

                    return NULL;

                }

