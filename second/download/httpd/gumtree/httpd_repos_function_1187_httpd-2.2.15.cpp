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
        /*
         * Reset vary_this if the novary flag is set for this condition.
         */
        if (c->flags & CONDFLAG_NOVARY) {
            ctx->vary_this = NULL;
        }
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
        newuri = do_expand(p->output, ctx, p);
        rewritelog((r, 2, ctx->perdir, "rewrite '%s' -> '%s'", ctx->uri,
                    newuri));
    }

    /* expand [E=var:val] and [CO=<cookie>] */
    do_expand_env(p->env, ctx);
    do_expand_cookie(p->cookie, ctx);

    /* non-substitution rules ('RewriteRule <pat> -') end here. */
    if (p->flags & RULEFLAG_NOSUB) {
        force_type_handler(p, ctx);

        if (p->flags & RULEFLAG_STATUS) {
            rewritelog((r, 2, ctx->perdir, "forcing responsecode %d for %s",
                        p->forced_responsecode, r->filename));

            r->status = p->forced_responsecode;
        }

        return 2;
    }

    /* Now adjust API's knowledge about r->filename and r->args */
    r->filename = newuri;

    if (ctx->perdir && (p->flags & RULEFLAG_DISCARDPATHINFO)) {
        r->path_info = NULL; 
    }

    splitout_queryargs(r, p->flags & RULEFLAG_QSAPPEND);

    /* Add the previously stripped per-directory location prefix, unless
     * (1) it's an absolute URL path and
     * (2) it's a full qualified URL
     */
    if (   ctx->perdir && !is_proxyreq && *r->filename != '/'
        && !is_absolute_uri(r->filename)) {
        rewritelog((r, 3, ctx->perdir, "add per-dir prefix: %s -> %s%s",
                    r->filename, ctx->perdir, r->filename));

        r->filename = apr_pstrcat(r->pool, ctx->perdir, r->filename, NULL);
    }

    /* If this rule is forced for proxy throughput
     * (`RewriteRule ... ... [P]') then emulate mod_proxy's
     * URL-to-filename handler to be sure mod_proxy is triggered
     * for this URL later in the Apache API. But make sure it is
     * a fully-qualified URL. (If not it is qualified with
     * ourself).
     */
    if (p->flags & RULEFLAG_PROXY) {
       /* For rules evaluated in server context, the mod_proxy fixup
        * hook can be relied upon to escape the URI as and when
        * necessary, since it occurs later.  If in directory context,
        * the ordering of the fixup hooks is forced such that
        * mod_proxy comes first, so the URI must be escaped here
        * instead.  See PR 39746, 46428, and other headaches. */
       if (ctx->perdir && (p->flags & RULEFLAG_NOESCAPE) == 0) {
           char *old_filename = r->filename;

           r->filename = ap_escape_uri(r->pool, r->filename);
           rewritelog((r, 2, ctx->perdir, "escaped URI in per-dir context "
                       "for proxy, %s -> %s", old_filename, r->filename));
       }

        fully_qualify_uri(r);

        rewritelog((r, 2, ctx->perdir, "forcing proxy-throughput with %s",
                    r->filename));

        r->filename = apr_pstrcat(r->pool, "proxy:", r->filename, NULL);
        return 1;
    }

    /* If this rule is explicitly forced for HTTP redirection
     * (`RewriteRule .. .. [R]') then force an external HTTP
     * redirect. But make sure it is a fully-qualified URL. (If
     * not it is qualified with ourself).
     */
    if (p->flags & RULEFLAG_FORCEREDIRECT) {
        fully_qualify_uri(r);

        rewritelog((r, 2, ctx->perdir, "explicitly forcing redirect with %s",
                    r->filename));

        r->status = p->forced_responsecode;
        return 1;
    }

    /* Special Rewriting Feature: Self-Reduction
     * We reduce the URL by stripping a possible
     * http[s]://<ourhost>[:<port>] prefix, i.e. a prefix which
     * corresponds to ourself. This is to simplify rewrite maps
     * and to avoid recursion, etc. When this prefix is not a
     * coincidence then the user has to use [R] explicitly (see
     * above).
     */
    reduce_uri(r);

    /* If this rule is still implicitly forced for HTTP
     * redirection (`RewriteRule .. <scheme>://...') then
     * directly force an external HTTP redirect.
     */
    if (is_absolute_uri(r->filename)) {
        rewritelog((r, 2, ctx->perdir, "implicitly forcing redirect (rc=%d) "
                    "with %s", p->forced_responsecode, r->filename));

        r->status = p->forced_responsecode;
        return 1;
    }

    /* Finally remember the forced mime-type */
    force_type_handler(p, ctx);

    /* Puuhhhhhhhh... WHAT COMPLICATED STUFF ;_)
     * But now we're done for this particular rule.
     */
    return 1;
}