static int apply_rewrite_list(request_rec *r, apr_array_header_t *rewriterules,
                              char *perdir)
{
    rewriterule_entry *entries;
    rewriterule_entry *p;
    int i;
    int changed;
    int rc;
    int s;

    /*
     *  Iterate over all existing rules
     */
    entries = (rewriterule_entry *)rewriterules->elts;
    changed = 0;
    loop:
    for (i = 0; i < rewriterules->nelts; i++) {
        p = &entries[i];

        /*
         *  Ignore this rule on subrequests if we are explicitly
         *  asked to do so or this is a proxy-throughput or a
         *  forced redirect rule.
         */
        if (r->main != NULL &&
            (p->flags & RULEFLAG_IGNOREONSUBREQ ||
             p->flags & RULEFLAG_PROXY          ||
             p->flags & RULEFLAG_FORCEREDIRECT    )) {
            continue;
        }

        /*
         *  Apply the current rule.
         */
        rc = apply_rewrite_rule(r, p, perdir);
        if (rc) {
            /*
             *  Indicate a change if this was not a match-only rule.
             */
            if (rc != 2) {
                changed = ((p->flags & RULEFLAG_NOESCAPE)
                           ? ACTION_NOESCAPE : ACTION_NORMAL);
            }

            /*
             *  Pass-Through Feature (`RewriteRule .. .. [PT]'):
             *  Because the Apache 1.x API is very limited we
             *  need this hack to pass the rewritten URL to other
             *  modules like mod_alias, mod_userdir, etc.
             */
            if (p->flags & RULEFLAG_PASSTHROUGH) {
                rewritelog(r, 2, "forcing '%s' to get passed through "
                           "to next API URI-to-filename handler", r->filename);
                r->filename = apr_pstrcat(r->pool, "passthrough:",
                                         r->filename, NULL);
                changed = ACTION_NORMAL;
                break;
            }

            /*
             *  Rule has the "forbidden" flag set which means that
             *  we stop processing and indicate this to the caller.
             */
            if (p->flags & RULEFLAG_FORBIDDEN) {
                rewritelog(r, 2, "forcing '%s' to be forbidden", r->filename);
                r->filename = apr_pstrcat(r->pool, "forbidden:",
                                         r->filename, NULL);
                changed = ACTION_NORMAL;
                break;
            }

            /*
             *  Rule has the "gone" flag set which means that
             *  we stop processing and indicate this to the caller.
             */
            if (p->flags & RULEFLAG_GONE) {
                rewritelog(r, 2, "forcing '%s' to be gone", r->filename);
                r->filename = apr_pstrcat(r->pool, "gone:", r->filename, NULL);
                changed = ACTION_NORMAL;
                break;
            }

            /*
             *  Stop processing also on proxy pass-through and
             *  last-rule and new-round flags.
             */
            if (p->flags & RULEFLAG_PROXY) {
                break;
            }
            if (p->flags & RULEFLAG_LASTRULE) {
                break;
            }

            /*
             *  On "new-round" flag we just start from the top of
             *  the rewriting ruleset again.
             */
            if (p->flags & RULEFLAG_NEWROUND) {
                goto loop;
            }

            /*
             *  If we are forced to skip N next rules, do it now.
             */
            if (p->skip > 0) {
                s = p->skip;
                while (   i < rewriterules->nelts
                       && s > 0) {
                    i++;
                    p = &entries[i];
                    s--;
                }
            }
        }
        else {
            /*
             *  If current rule is chained with next rule(s),
             *  skip all this next rule(s)
             */
            while (   i < rewriterules->nelts
                   && p->flags & RULEFLAG_CHAIN) {
                i++;
                p = &entries[i];
            }
        }
    }
    return changed;
}