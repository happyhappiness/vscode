
            /*
             *  On "new-round" flag we just start from the top of
             *  the rewriting ruleset again.
             */
            if (p->flags & RULEFLAG_NEWROUND) {
                if (++round >= p->maxrounds) { 
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02596)
                                  "RewriteRule '%s' and URI '%s' exceeded "
                                  "maximum number of rounds (%d) via the [N] flag", 
                                  p->pattern, r->uri, p->maxrounds);

                    r->status = HTTP_INTERNAL_SERVER_ERROR;
                    return ACTION_STATUS; 
                }
                goto loop;
            }

            /*
             *  If we are forced to skip N next rules, do it now.
             */
