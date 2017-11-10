static int apply_rewrite_rule(request_rec *r, rewriterule_entry *p,
                              char *perdir)
{
    char *uri;
    char *output;
    const char *vary;
    char newuri[MAX_STRING_LEN];
    regex_t *regexp;
    regmatch_t regmatch[AP_MAX_REG_MATCH];
    backrefinfo *briRR = NULL;
    backrefinfo *briRC = NULL;
    int failed;
    apr_array_header_t *rewriteconds;
    rewritecond_entry *conds;
    rewritecond_entry *c;
    int i;
    int rc;
    int is_proxyreq = 0;

    /*
     *  Initialisation
     */
    uri     = r->filename;
    regexp  = p->regexp;
    output  = p->output;

    /*
     *  Add (perhaps splitted away) PATH_INFO postfix to URL to
     *  make sure we really match against the complete URL.
     */
    if (perdir != NULL && r->path_info != NULL && r->path_info[0] != '\0') {
        rewritelog(r, 3, "[per-dir %s] add path info postfix: %s -> %s%s",
                   perdir, uri, uri, r->path_info);
        uri = apr_pstrcat(r->pool, uri, r->path_info, NULL);
    }

    /*
     *  On per-directory context (.htaccess) strip the location
     *  prefix from the URL to make sure patterns apply only to
     *  the local part.  Additionally indicate this special
     *  threatment in the logfile.
     */
    if (perdir) {
        /*
  	     * Proxy request?
         */
  	    is_proxyreq = (   r->proxyreq && r->filename
  	                   && !strncmp(r->filename, "proxy:", 6));

        if (   !is_proxyreq && strlen(uri) >= strlen(perdir)
            && strncmp(uri, perdir, strlen(perdir)) == 0) {
            rewritelog(r, 3, "[per-dir %s] strip per-dir prefix: %s -> %s",
                       perdir, uri, uri+strlen(perdir));
            uri = uri+strlen(perdir);
        }
    }

    /*
     *  Try to match the URI against the RewriteRule pattern
     *  and exit immeddiately if it didn't apply.
     */
    if (perdir == NULL) {
        rewritelog(r, 3, "applying pattern '%s' to uri '%s'",
                   p->pattern, uri);
    }
    else {
        rewritelog(r, 3, "[per-dir %s] applying pattern '%s' to uri '%s'",
                   perdir, p->pattern, uri);
    }
    rc = (ap_regexec(regexp, uri, AP_MAX_REG_MATCH, regmatch, 0) == 0);
    if (! (( rc && !(p->flags & RULEFLAG_NOTMATCH)) ||
           (!rc &&  (p->flags & RULEFLAG_NOTMATCH))   ) ) {
        return 0;
    }

    /*
     *  Else create the RewriteRule `regsubinfo' structure which
     *  holds the substitution information.
     */
    briRR = (backrefinfo *)apr_palloc(r->pool, sizeof(backrefinfo));
    if (!rc && (p->flags & RULEFLAG_NOTMATCH)) {
        /*  empty info on negative patterns  */
        briRR->source = "";
        briRR->nsub   = 0;
    }
    else {
        briRR->source = apr_pstrdup(r->pool, uri);
        briRR->nsub   = regexp->re_nsub;
        memcpy((void *)(briRR->regmatch), (void *)(regmatch),
               sizeof(regmatch));
    }

    /*
     *  Initiallally create the RewriteCond backrefinfo with
     *  empty backrefinfo, i.e. not subst parts
     *  (this one is adjusted inside apply_rewrite_cond() later!!)
     */
    briRC = (backrefinfo *)apr_pcalloc(r->pool, sizeof(backrefinfo));
    briRC->source = "";
    briRC->nsub   = 0;

    /*
     *  Ok, we already know the pattern has matched, but we now
     *  additionally have to check for all existing preconditions
     *  (RewriteCond) which have to be also true. We do this at
     *  this very late stage to avoid unnessesary checks which
     *  would slow down the rewriting engine!!
     */
    rewriteconds = p->rewriteconds;
    conds = (rewritecond_entry *)rewriteconds->elts;
    failed = 0;
    for (i = 0; i < rewriteconds->nelts; i++) {
        c = &conds[i];
        rc = apply_rewrite_cond(r, c, perdir, briRR, briRC);
        if (c->flags & CONDFLAG_ORNEXT) {
            /*
             *  The "OR" case
             */
            if (rc == 0) {
                /*  One condition is false, but another can be
                 *  still true, so we have to continue...
                 */
                apr_table_unset(r->notes, VARY_KEY_THIS);
                continue;
            }
            else {
                /*  One true condition is enough in "or" case, so
                 *  skip the other conditions which are "ornext"
                 *  chained
                 */
                while (   i < rewriteconds->nelts
                       && c->flags & CONDFLAG_ORNEXT) {
                    i++;
                    c = &conds[i];
                }
                continue;
            }
        }
        else {
            /*
             *  The "AND" case, i.e. no "or" flag,
             *  so a single failure means total failure.
             */
            if (rc == 0) {
                failed = 1;
                break;
            }
        }
        vary = apr_table_get(r->notes, VARY_KEY_THIS);
        if (vary != NULL) {
            apr_table_merge(r->notes, VARY_KEY, vary);
            apr_table_unset(r->notes, VARY_KEY_THIS);
        }
    }
    /*  if any condition fails the complete rule fails  */
    if (failed) {
        apr_table_unset(r->notes, VARY_KEY);
        apr_table_unset(r->notes, VARY_KEY_THIS);
        return 0;
    }

    /*
     * Regardless of what we do next, we've found a match.  Check to see
     * if any of the request header fields were involved, and add them
     * to the Vary field of the response.
     */
    if ((vary = apr_table_get(r->notes, VARY_KEY)) != NULL) {
        apr_table_merge(r->headers_out, "Vary", vary);
        apr_table_unset(r->notes, VARY_KEY);
    }

    /*
     *  If this is a pure matching rule (`RewriteRule <pat> -')
     *  we stop processing and return immediately. The only thing
     *  we have not to forget are the environment variables and
     *  cookies:
     *  (`RewriteRule <pat> - [E=...,CO=...]')
     */
    if (strcmp(output, "-") == 0) {
        do_expand_env(r, p->env, briRR, briRC);
        do_expand_cookie(r, p->cookie, briRR, briRC);
        if (p->forced_mimetype != NULL) {
            if (perdir == NULL) {
                /* In the per-server context we can force the MIME-type
                 * the correct way by notifying our MIME-type hook handler
                 * to do the job when the MIME-type API stage is reached.
                 */
                rewritelog(r, 2, "remember %s to have MIME-type '%s'",
                           r->filename, p->forced_mimetype);
                apr_table_setn(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR,
                               p->forced_mimetype);
            }
            else {
                /* In per-directory context we operate in the Fixup API hook
                 * which is after the MIME-type hook, so our MIME-type handler
                 * has no chance to set r->content_type. And because we are
                 * in the situation where no substitution takes place no
                 * sub-request will happen (which could solve the
                 * restriction). As a workaround we do it ourself now
                 * immediately although this is not strictly API-conforming.
                 * But it's the only chance we have...
                 */
                rewritelog(r, 1, "[per-dir %s] force %s to have MIME-type "
                           "'%s'", perdir, r->filename, p->forced_mimetype);
                ap_set_content_type(r, p->forced_mimetype);
            }
        }
        return 2;
    }

    /*
     *  Ok, now we finally know all patterns have matched and
     *  that there is something to replace, so we create the
     *  substitution URL string in `newuri'.
     */
    do_expand(r, output, newuri, sizeof(newuri), briRR, briRC);
    if (perdir == NULL) {
        rewritelog(r, 2, "rewrite %s -> %s", uri, newuri);
    }
    else {
        rewritelog(r, 2, "[per-dir %s] rewrite %s -> %s", perdir, uri, newuri);
    }

    /*
     *  Additionally do expansion for the environment variable
     *  strings (`RewriteRule .. .. [E=<string>]').
     */
    do_expand_env(r, p->env, briRR, briRC);

    /*
     *  Also set cookies for any cookie strings
     *  (`RewriteRule .. .. [CO=<string>]').
     */
    do_expand_cookie(r, p->cookie, briRR, briRC);

    /*
     *  Now replace API's knowledge of the current URI:
     *  Replace r->filename with the new URI string and split out
     *  an on-the-fly generated QUERY_STRING part into r->args
     */
    r->filename = apr_pstrdup(r->pool, newuri);
    splitout_queryargs(r, p->flags & RULEFLAG_QSAPPEND);

    /*
     *   Add the previously stripped per-directory location
     *   prefix if the new URI is not a new one for this
     *   location, i.e. if it's not an absolute URL (!) path nor
     *   a fully qualified URL scheme.
     */
    if (   perdir && !is_proxyreq && *r->filename != '/'
        && !is_absolute_uri(r->filename)) {
        rewritelog(r, 3, "[per-dir %s] add per-dir prefix: %s -> %s%s",
                   perdir, r->filename, perdir, r->filename);
        r->filename = apr_pstrcat(r->pool, perdir, r->filename, NULL);
    }

    /*
     *  If this rule is forced for proxy throughput
     *  (`RewriteRule ... ... [P]') then emulate mod_proxy's
     *  URL-to-filename handler to be sure mod_proxy is triggered
     *  for this URL later in the Apache API. But make sure it is
     *  a fully-qualified URL. (If not it is qualified with
     *  ourself).
     */
    if (p->flags & RULEFLAG_PROXY) {
        fully_qualify_uri(r);
        if (perdir == NULL) {
            rewritelog(r, 2, "forcing proxy-throughput with %s", r->filename);
        }
        else {
            rewritelog(r, 2, "[per-dir %s] forcing proxy-throughput with %s",
                       perdir, r->filename);
        }
        r->filename = apr_pstrcat(r->pool, "proxy:", r->filename, NULL);
        return 1;
    }

    /*
     *  If this rule is explicitly forced for HTTP redirection
     *  (`RewriteRule .. .. [R]') then force an external HTTP
     *  redirect. But make sure it is a fully-qualified URL. (If
     *  not it is qualified with ourself).
     */
    if (p->flags & RULEFLAG_FORCEREDIRECT) {
        fully_qualify_uri(r);
        if (perdir == NULL) {
            rewritelog(r, 2,
                       "explicitly forcing redirect with %s", r->filename);
        }
        else {
            rewritelog(r, 2,
                       "[per-dir %s] explicitly forcing redirect with %s",
                       perdir, r->filename);
        }
        r->status = p->forced_responsecode;
        return 1;
    }

    /*
     *  Special Rewriting Feature: Self-Reduction
     *  We reduce the URL by stripping a possible
     *  http[s]://<ourhost>[:<port>] prefix, i.e. a prefix which
     *  corresponds to ourself. This is to simplify rewrite maps
     *  and to avoid recursion, etc. When this prefix is not a
     *  coincidence then the user has to use [R] explicitly (see
     *  above).
     */
    reduce_uri(r);

    /*
     *  If this rule is still implicitly forced for HTTP
     *  redirection (`RewriteRule .. <scheme>://...') then
     *  directly force an external HTTP redirect.
     */
    if (is_absolute_uri(r->filename)) {
        if (perdir == NULL) {
            rewritelog(r, 2,
                       "implicitly forcing redirect (rc=%d) with %s",
                       p->forced_responsecode, r->filename);
        }
        else {
            rewritelog(r, 2, "[per-dir %s] implicitly forcing redirect "
                       "(rc=%d) with %s", perdir, p->forced_responsecode,
                       r->filename);
        }
        r->status = p->forced_responsecode;
        return 1;
    }

    /*
     *  Finally we had to remember if a MIME-type should be
     *  forced for this URL (`RewriteRule .. .. [T=<type>]')
     *  Later in the API processing phase this is forced by our
     *  MIME API-hook function. This time it's no problem even for
     *  the per-directory context (where the MIME-type hook was
     *  already processed) because a sub-request happens ;-)
     */
    if (p->forced_mimetype != NULL) {
        apr_table_setn(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR,
                      p->forced_mimetype);
        if (perdir == NULL) {
            rewritelog(r, 2, 