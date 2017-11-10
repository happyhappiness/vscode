static int apply_rewrite_rule(rewriterule_entry *p, rewrite_ctx *ctx)
{
    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
    apr_array_header_t *rewriteconds;
    rewritecond_entry *conds;
    int i, rc;
    char *newuri = NULL;
    request_rec *r = ctx->r;
    int is_proxyreq = 0;

    ctx->uri = r->filename;

    if (ctx->perdir) {
        apr_size_t dirlen = strlen(ctx->perdir);

        /*
         * Proxy request?
         */
        is_proxyreq = (   r->proxyreq && r->filename
                       && !strncmp(r->filename, "proxy:", 6));

        /* Since we want to match against the (so called) full URL, we have
         * to re-add the PATH_INFO postfix
         */
        if (r->path_info && *r->path_info) {
            rewritelog((r, 3, ctx->perdir, "add path info postfix: %s -> %s%s",
                        ctx->uri, ctx->uri, r->path_info));
            ctx->uri = apr_pstrcat(r->pool, ctx->uri, r->path_info, NULL);
        }

        /* Additionally we strip the physical path from the url to match
         * it independent from the underlaying filesystem.
         */
        if (!is_proxyreq && strlen(ctx->uri) >= dirlen &&
            !strncmp(ctx->uri, ctx->perdir, dirlen)) {

            rewritelog((r, 3, ctx->perdir, "strip per-dir prefix: %s -> %s",
                        ctx->uri, ctx->uri + dirlen));
            ctx->uri = ctx->uri + dirlen;
        }
    }

    /* Try to match the URI against the RewriteRule pattern
     * and exit immediately if it didn't apply.
     */
    rewritelog((r, 3, ctx->perdir, "applying pattern '%s' to uri '%s'",
                p->pattern, ctx->uri));

    rc = !ap_regexec(p->regexp, ctx->uri, AP_MAX_REG_MATCH, regmatch, 0);
    if (! (( rc && !(p->flags & RULEFLAG_NOTMATCH)) ||
           (!rc &&  (p->flags & RULEFLAG_NOTMATCH))   ) ) {
        return 0;
    }

    /* It matched, wow! Now it's time to prepare the context structure for
     * further processing
     */
    ctx->vary_this = NULL;
    ctx->briRC.source = NULL;

    if (p->flags & RULEFLAG_NOTMATCH) {
        ctx->briRR.source = NULL;
    }
    else {
        ctx->briRR.source = apr_pstrdup(r->pool, ctx->uri);
        ctx->briRR.nsub   = p->regexp->re_nsub;
        memcpy(ctx->briRR.regmatch, regmatch, sizeof(regmatch));
    }

    /* Ok, we already know the pattern has matched, but we now
     * additionally have to check for all existing preconditions
     * (RewriteCond) which have to be also true. We do this at
     * this very late stage to avoid unnessesary checks which
     * would slow down the rewriting engine.
     */
    rewriteconds = p->rewriteconds;
    conds = (rewritecond_entry *)rewriteconds->elts;

    for (i = 0; i < rewriteconds->nelts; ++i) {
        rewritecond_entry *c = &conds[i];

        rc = apply_rewrite_cond(c, ctx);
        if (c->flags & CONDFLAG_ORNEXT) {
            if (!rc) {
                /* One condition is false, but another can be still true. */
                ctx->vary_this = NULL;
                continue;
            }
            else {
                /* skip the rest of the chained OR conditions */
                while (   i < rewriteconds->nelts
                       && c->flags & CONDFLAG_ORNEXT) {
                    c = &conds[++i];
                }
                continue;
            }
        }
        else if (!rc) {
            return 0;
        }

        /* If some HTTP header was involved in the condition, remember it
         * for later use
         */
        if (ctx->vary_this) {
            ctx->vary = ctx->vary
                        ? apr_pstrcat(r->pool, ctx->vary, ", ", ctx->vary_this,
                                      NULL)
                        : ctx->vary_this;
            ctx->vary_this = NULL;
        }
    }

    /* expand the result */
    if (!(p->flags & RULEFLAG_NOSUB)) {
        newuri = do_expand(p->output, ctx);
        rewritelog((r, 2, ctx->perdir, "rewrite '%s' -> '%s'", ctx->uri,
                    newuri));
    }

    /* expand [E=var:val] and [CO=<cookie>] */
    do_expand_env(p->env, ctx);
    do_expand_cookie