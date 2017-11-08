static int hook_fixup(request_rec *r)
{
    rewrite_perdir_conf *dconf;
    char *cp;
    char *cp2;
    const char *ccp;
    apr_size_t l;
    int rulestatus;
    int n;
    char *ofilename, *oargs;
    int is_proxyreq;
    void *skipdata;

    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
                                                        &rewrite_module);

    /* if there is no per-dir config we return immediately */
    if (dconf == NULL) {
        return DECLINED;
    }

    /*
     * only do something under runtime if the engine is really enabled,
     * for this directory, else return immediately!
     */
    if (dconf->state == ENGINE_DISABLED) {
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
     *  Ignore such attempts, allowing mod_dir to direct the client to the
     *  canonical URL. This can be controlled with the AllowNoSlash option.
     */
    if (!is_proxyreq && !(dconf->options & OPTION_NOSLASH)) {
        l = strlen(dconf->directory) - 1;
        if (r->filename && strlen(r->filename) == l &&
            (dconf->directory)[l] == '/' &&
            !strncmp(r->filename, dconf->directory, l)) {
            return DECLINED;
        }
    }

    /* END flag was used as a RewriteRule flag on this request */
    apr_pool_userdata_get(&skipdata, really_last_key, r->pool);
    if (skipdata != NULL) {
        rewritelog((r, 8, dconf->directory, "Declining, no further rewriting due to END flag"));
        return DECLINED;
    }

    /*
     *  Do the Options check after engine check, so
     *  the user is able to explicitely turn RewriteEngine Off.
     */
    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
        /* FollowSymLinks is mandatory! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00670)
                     "Options FollowSymLinks and SymLinksIfOwnerMatch are both off, "
                     "so the RewriteRule directive is also forbidden "
                     "due to its similar ability to circumvent directory restrictions : "
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
    oargs = r->args;

    if (r->filename == NULL) {
        r->filename = apr_pstrdup(r->pool, r->uri);
        rewritelog((r, 2, dconf->directory, "init rewrite engine with"
                   " requested uri %s", r->filename));
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
                /* see proxy_http:proxy_http_canon() */
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
        else if ((skip = is_absolute_uri(r->filename, NULL)) > 0) {
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
                char *escaped_args = NULL;
                int noescape = (rulestatus == ACTION_NOESCAPE ||
                                (oargs && !strcmp(r->args, oargs)));

                r->filename = apr_pstrcat(r->pool, r->filename, "?",
                                          noescape
                                            ? r->args
                                            : (escaped_args = ap_escape_uri(r->pool, r->args)),
                                          NULL);

                rewritelog((r, 1, dconf->directory, "%s %s to query string for redirect %s",
                            noescape ? "copying" : "escaping",
                            r->args ,
                            noescape ? "" : escaped_args));
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
            if (   *r->filename != '/'
                && !ap_os_is_path_absolute(r->pool, r->filename)) {
                return HTTP_BAD_REQUEST;
            }

            /* Check for deadlooping:
             * At this point we KNOW that at least one rewriting
             * rule was applied, but when the resulting URL is
             * the same as the initial URL, we are not allowed to
             * use the following internal redirection stuff because
             * this would lead to a deadloop.
             */
            if (ofilename != NULL && strcmp(r->filename, ofilename) == 0) {
                rewritelog((r, 1, dconf->directory, "initial URL equal rewritten"
                            " URL: %s [IGNORING REWRITE]", r->filename));
                return OK;
            }

            /* if there is a valid base-URL then substitute
             * the per-dir prefix with this base-URL if the
             * current filename still is inside this per-dir
             * context. If not then treat the result as a
             * plain URL
             */
            if (dconf->baseurl != NULL) {
                rewritelog((r, 2, dconf->directory, "trying to replace prefix "
                            "%s with %s", dconf->directory, dconf->baseurl));

                r->filename = subst_prefix_path(r, r->filename,
                                                dconf->directory,
                                                dconf->baseurl);
            }
            else {
                /* if no explicit base-URL exists we assume
                 * that the directory prefix is also a valid URL
                 * for this webserver and only try to remove the
                 * document_root if it is prefix
                 */
                if ((ccp = ap_document_root(r)) != NULL) {
                    /* strip trailing slash */
                    l = strlen(ccp);
                    if (ccp[l-1] == '/') {
                        --l;
                    }
                    if (!strncmp(r->filename, ccp, l) &&
                        r->filename[l] == '/') {
                        rewritelog((r, 2,dconf->directory, "strip document_root"
                                    " prefix: %s -> %s", r->filename,
                                    r->filename+l));

                        r->filename = apr_pstrdup(r->pool, r->filename+l);
                    }
                }
            }

            /* now initiate the internal redirect */
            rewritelog((r, 1, dconf->directory, "internal redirect with %s "
                        "[INTERNAL REDIRECT]", r->filename));
            r->filename = apr_pstrcat(r->pool, "redirect:", r->filename, NULL);
            r->handler = REWRITE_REDIRECT_HANDLER_NAME;
            return OK;
        }
    }
    else {
        rewritelog((r, 1, dconf->directory, "pass through %s", r->filename));
        r->filename = ofilename;
        return DECLINED;
    }
}