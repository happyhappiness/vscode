static int apply_rewrite_list(request_rec *r, apr_array_header_t *rewriterules,
                              char *perdir)
{
    rewriterule_entry *entries;
    rewriterule_entry *p;
    int i;
    int changed;
    int rc;
    int s;
    rewrite_ctx *ctx;
    int round = 1;

    ctx = apr_palloc(r->pool, sizeof(*ctx));
    ctx->perdir = perdir;
    ctx->r = r;

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
             p->flags & RULEFLAG_FORCEREDIRECT    )) {
            continue;
        }

        /*
         *  Apply the current rule.
         */
        ctx->vary = NULL;
        rc = apply_rewrite_rule(p, ctx);

        if (rc) {

            /* Catch looping rules with pathinfo growing unbounded */
            if ( strlen( r->filename ) > 2*r->server->limit_req_line ) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "RewriteRule '%s' and URI '%s' "
                              "exceeded maximum length (%d)", 
                              p->pattern, r->uri, 2*r->server->limit_req_line );
                r->status = HTTP_INTERNAL_SERVER_ERROR;
                return ACTION_STATUS;
            }

            /* Regardless of what we do next, we've found a match. Check to see
             * if any of the request header fields were involved, and add them
             * to the Vary field of the response.
             */
            if (ctx->vary) {
                apr_table_merge(r->headers_out, "Vary", ctx->vary);
            }

            /*
             * The rule sets the response code (implies match-only)
             */
            if (p->flags & RULEFLAG_STATUS) {
                return ACTION_STATUS;
            }

            /*
             * Indicate a change if this was not a match-only rule.
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
                rewritelog((r, 2, perdir, "forcing '%s' to get passed through "
                           "to next API URI-to-filename handler", r->filename));
                r->filename = apr_pstrcat(r->pool, "passthrough:",
                                         r->filename, NULL);
                changed = ACTION_NORMAL;
                break;
            }

            if (p->flags & RULEFLAG_END) {
                rewritelog((r, 8, perdir, "Rule has END flag, no further rewriting for this request"));
                apr_pool_userdata_set("1", really_last_key, apr_pool_cleanup_null, r->pool);
                break;
            }
            /*
             *  Stop processing also on proxy pass-through and
             *  last-rule and new-round flags.
             */
            if (p->flags & (RULEFLAG_PROXY | RULEFLAG_LASTRULE)) {
                break;
            }

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
            if (p->skip > 0) {
                s = p->skip;
                while (   i < rewriterules->nelts
                       && s > 0) {
                    i++;
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