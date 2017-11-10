static int hook_fixup(request_rec *r)
{
    rewrite_perdir_conf *dconf;
    char *cp;
    char *cp2;
    const char *ccp;
    apr_size_t l;
    int rulestatus;
    int n;
    char *ofilename;
    int is_proxyreq;

    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
                                                        &rewrite_module);

    /* if there is no per-dir config we return immediately */
    if (dconf == NULL) {
        return DECLINED;
    }

    /* if there are no real (i.e. no RewriteRule directives!)
       per-dir config of us, we return also immediately */
    if (dconf->directory == NULL) {
        return DECLINED;
    }

    /*
     * Proxy request?
     */
    is_proxyreq = (   r->proxyreq && r->filename
                   && !strncmp(r->filename, "proxy:", 6));

    /*
     *  .htaccess file is called before really entering the directory, i.e.:
     *  URL: http://localhost/foo  and .htaccess is located in foo directory
     *  Ignore such attempts, since they may lead to undefined behaviour.
     */
    if (!is_proxyreq) {
        l = strlen(dconf->directory) - 1;
        if (r->filename && strlen(r->filename) == l &&
            (dconf->directory)[l] == '/' &&
            !strncmp(r->filename, dconf->directory, l)) {
            return DECLINED;
        }
    }

    /*
     *  only do something under runtime if the engine is really enabled,
     *  for this directory, else return immediately!
     */
    if (dconf->state == ENGINE_DISABLED) {
        return DECLINED;
    }

    /*
     *  Do the Options check after engine check, so
     *  the user is able to explicitely turn RewriteEngine Off.
     */
    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
        /* FollowSymLinks is mandatory! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
                     "which implies that RewriteRule directive is forbidden: "
                     "%s", r->filename);
        return HTTP_FORBIDDEN;
    }

    /*
     *  remember the current filename before rewriting for later check
     *  to prevent deadlooping because of internal redirects
     *  on final URL/filename which can be equal to the inital one.
     *  also, we'll restore original r->filename if we decline this
     *  request
     */
    ofilename = r->filename;

    if (r->filename == NULL) {
        r->filename = apr_pstrdup(r->pool, r->uri);
        rewritelog((r, 2, "init rewrite engine with requested uri %s",
                    r->filename));
    }

    /*
     *  now apply the rules ...
     */
    rulestatus = apply_rewrite_list(r, dconf->rewriterules, dconf->directory);
    if (rulestatus) {
        unsigned skip;

        if (ACTION_STATUS == rulestatus) {
            int n = r->status;

            r->status = HTTP_OK;
            return n;
        }

        l = strlen(r->filename);
        if (l > 6 && strncmp(r->filename, "proxy:", 6) == 0) {
            /* it should go on as an internal proxy request */

            /* make sure the QUERY_STRING and
             * PATH_INFO parts get incorporated
             * (r->path_info was already appended by the
             * rewriting engine because of the per-dir context!)
             */
            if (r->args != NULL) {
                r->filename = apr_pstrcat(r->pool, r->filename,
                                          "?", r->args, NULL);
            }

            /* now make sure the request gets handled by the proxy handler */
            if (PROXYREQ_NONE == r->proxyreq) {
                r->proxyreq = PROXYREQ_REVERSE;
            }
            r->handler  = "proxy-server";

            rewritelog((r, 1, dconf->directory, "go-ahead with proxy request "
                        "%s [OK]", r->filename));
            return OK;
        }
        else if ((skip = is_absolute_uri(r->filename)) > 0) {
            /* it was finally rewritten to a remote URL */

            /* because we are in a per-dir context
             * first try to replace the directory with its base-URL
             * if there is a base-URL available
             */
            if (dconf->baseurl != NULL) {
                /* skip 'scheme://' */
                cp = r->filename + skip;

                if ((cp = ap_strchr(cp, '/')) != NULL && *(++cp)) {
                    rewritelog((r, 2, dconf->directory,
                                "trying to replace prefix %s with %s",
                                dconf->directory, dconf->baseurl));

                    /* I think, that hack needs an explanation:
                     * well, here is it:
                     * mod_rewrite was written for unix systems, were
                     * absolute file-system paths start with a slash.
                     * URL-paths _also_ start with slashes, so they
                     * can be easily compared with system paths.
                     *
                     * the following assumes, that the actual url-path
                     * may be prefixed by the current directory path and
                     * tries to replace the system path with the RewriteBase
                     * URL.
                     * That assumption is true if we use a RewriteRule like
                     *
                     * RewriteRule ^foo bar [R]
                     *
                     * (see apply_rewrite_rule function)
                     * However on systems that don't have a / as system
                     * root this will never match, so we skip the / after the
                     * hostname and compare/substitute only the stuff after it.
                     *
                     * (note that cp was already increased to the right value)
                     */
                    cp2 = subst_prefix_path(r, cp, (*dconf->directory == '/')
                                                   ? dconf->directory + 1
                                                   : dconf->directory,
                                            dconf->baseurl + 1);
                    if (strcmp(cp2, cp) != 0) {
                        *cp = '\0';
                        r->filename = apr_pstrcat(r->pool, r->filename,
                                                  cp2, NULL);
                    }
                }
            }

            /* now prepare the redirect... */
            if (rulestatus != ACTION_NOESCAPE) {
                rewritelog((r, 1, dconf->directory, "escaping %s for redirect",
                            r->filename));
                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
            }

            /* append the QUERY_STRING part */
            if (r->args) {
                r->filename = apr_pstrcat(r->pool, r->filename, "?",
                                          (rulestatus == ACTION_NOESCAPE)
                                            ? r->args
                                            : ap_escape_uri(r->pool, r->args),
                                          NULL);
            }

            /* determine HTTP redirect response code */
            if (ap_is_HTTP_REDIRECT(r->status)) {
                n = r->status;
                r->status = HTTP_OK; /* make Apache kernel happy */
            }
            else {
                n = HTTP_MOVED_TEMPORARILY;
            }

            /* now do the redirection */
            apr_table_setn(r->headers_out, "Location", r->filename);
            rewritelog((r, 1, dconf->directory, "redirect to %s [REDIRECT/%d]",
                        r->filename, n));
            return n;
        }
        else {
            /* it was finally rewritten to a local path */

            /* if someone used the PASSTHROUGH flag in per-dir
             * context we just ignore it. It is only useful
             * in per-server context
             */
            if (l > 12 && strncmp(r->filename, "passthrough:", 12) == 0) {
                r->filename = apr_pstrdup(r->pool, r->filename+12);
            }

            /* the filename must be either an absolute local path or an
             * absolute local URL.
             */
            