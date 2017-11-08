static int hook_fixup(request_rec *r)
{
    rewrite_perdir_conf *dconf;
    char *cp;
    char *cp2;
    const char *ccp;
    char *prefix;
    int l;
    int rulestatus;
    int n;
    char *ofilename;

    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
                                                        &rewrite_module);

    /* if there is no per-dir config we return immediately */
    if (dconf == NULL) {
        return DECLINED;
    }

    /* we shouldn't do anything in subrequests */
    if (r->main != NULL) {
        return DECLINED;
    }

    /* if there are no real (i.e. no RewriteRule directives!)
       per-dir config of us, we return also immediately */
    if (dconf->directory == NULL) {
        return DECLINED;
    }

    /*
     *  only do something under runtime if the engine is really enabled,
     *  for this directory, else return immediately!
     */
    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
        /* FollowSymLinks is mandatory! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
                     "which implies that RewriteRule directive is forbidden: "
                     "%s", r->filename);
        return HTTP_FORBIDDEN;
    }
    else {
        /* FollowSymLinks is given, but the user can
         * still turn off the rewriting engine
         */
        if (dconf->state == ENGINE_DISABLED) {
            return DECLINED;
        }
    }

    /*
     *  remember the current filename before rewriting for later check
     *  to prevent deadlooping because of internal redirects
     *  on final URL/filename which can be equal to the inital one.
     */
    ofilename = r->filename;

    /*
     *  now apply the rules ...
     */
    rulestatus = apply_rewrite_list(r, dconf->rewriterules, dconf->directory);
    if (rulestatus) {

        if (strlen(r->filename) > 6 &&
            strncmp(r->filename, "proxy:", 6) == 0) {
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
            r->proxyreq = PROXYREQ_REVERSE;
            r->handler  = "proxy-server";

            rewritelog(r, 1, "[per-dir %s] go-ahead with proxy request "
                       "%s [OK]", dconf->directory, r->filename);
            return OK;
        }
        else if (is_absolute_uri(r->filename)) {
            /* it was finally rewritten to a remote URL */

            /* because we are in a per-dir context
             * first try to replace the directory with its base-URL
             * if there is a base-URL available
             */
            if (dconf->baseurl != NULL) {
                /* skip 'scheme:' */
                for (cp = r->filename; *cp != ':' && *cp != '\0'; cp++)
                    ;
                /* skip '://' */
                cp += 3;
                if ((cp = strchr(cp, '/')) != NULL) {
                    rewritelog(r, 2,
                               "[per-dir %s] trying to replace "
                               "prefix %s with %s",
                               dconf->directory, dconf->directory,
                               dconf->baseurl);
                    cp2 = subst_prefix_path(r, cp, dconf->directory,
                                            dconf->baseurl);
                    if (strcmp(cp2, cp) != 0) {
                        *cp = '\0';
                        r->filename = apr_pstrcat(r->pool, r->filename,
                                                 cp2, NULL);
                    }
                }
            }

            /* now prepare the redirect... */

            /* skip 'scheme:' */
            for (cp = r->filename; *cp != ':' && *cp != '\0'; cp++)
                ;
            /* skip '://' */
            cp += 3;
            /* skip host part */
            for ( ; *cp != '/' && *cp != '\0'; cp++)
                ;
            if (*cp != '\0') {
                if (rulestatus != ACTION_NOESCAPE) {
                    rewritelog(r, 1, "[per-dir %s] escaping %s for redirect",
                               dconf->directory, r->filename);
                    cp2 = ap_escape_uri(r->pool, cp);
                }
                else {
                    cp2 = apr_pstrdup(r->pool, cp);
                }
                *cp = '\0';
                r->filename = apr_pstrcat(r->pool, r->filename, cp2, NULL);
            }

            /* append the QUERY_STRING part */
            if (r->args != NULL) {
                char *args;
                if (rulestatus == ACTION_NOESCAPE) {
                    args = r->args;
                }
                else {
                    args = ap_escape_uri(r->pool, r->args);
                }
                r->filename = apr_pstrcat(r->pool, r->filename, "?", 
                                          args, NULL);
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
            rewritelog(r, 1, "[per-dir %s] redirect to %s [REDIRECT/%d]",
                       dconf->directory, r->filename, n);
            return n;
        }
        else if (strlen(r->filename) > 10 &&
                 strncmp(r->filename, "forbidden:", 10) == 0) {
            /* This URL is forced to be forbidden for the requester */
            return HTTP_FORBIDDEN;
        }
        else if (strlen(r->filename) > 5 &&
                 strncmp(r->filename, "gone:", 5) == 0) {
            /* This URL is forced to be gone */
            return HTTP_GONE;
        }
        else {
            /* it was finally rewritten to a local path */

            /* if someone used the PASSTHROUGH flag in per-dir
             * context we just ignore it. It is only useful
             * in per-server context
             */
            if (strlen(r->filename) > 12 &&
                strncmp(r->filename, "passthrough:", 12) == 0) {
                r->filename = apr_pstrdup(r->pool, r->filename+12);
            }

            /* the filename must be an absolute path! */
            if (!ap_os_is_path_absolute(r->pool, r->filename)) {
                return HTTP_BAD_REQUEST;
            }

            /* Check for deadlooping:
             * At this point we KNOW that at least one rewriting
             * rule was applied, but when the resulting URL is
             * the same as the initial URL, we are not allowed to
             * use the following internal redirection stuff because
             * this would lead to a deadloop.
             */
            if (strcmp(r->filename, ofilename) == 0) {
                rewritelog(r, 1, "[per-dir %s] initial URL equal rewritten "
                           "URL: %s [IGNORING REWRITE]",
                           dconf->directory, r->filename);
                return OK;
            }

            /* if there is a valid base-URL then substitute
             * the per-dir prefix with this base-URL if the
             * current filename still is inside this per-dir
             * context. If not then treat the result as a
             * plain URL
             */
            if (dconf->baseurl != NULL) {
                rewritelog(r, 2,
                           "[per-dir %s] trying to replace prefix %s with %s",
                           dconf->directory, dconf->directory, dconf->baseurl);
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
                    prefix = apr_pstrdup(r->pool, ccp);
                    /* always NOT have a trailing slash */
                    l = strlen(prefix);
                    if (prefix[l-1] == '/') {
                        prefix[l-1] = '\0';
                        l--;
                    }
                    if (strncmp(r->filename, prefix, l) == 0) {
                        rewritelog(r, 2,
                                   "[per-dir %s] strip document_root "
                                   "prefix: %s -> %s",
                                   dconf->directory, r->filename,
                                   r->filename+l);
                        r->filename = apr_pstrdup(r->pool, r->filename+l);
                    }
                }
            }

            /* now initiate the internal redirect */
            rewritelog(r, 1, "[per-dir %s] internal redirect with %s "
                       "[INTERNAL REDIRECT]", dconf->directory, r->filename);
            r->filename = apr_pstrcat(r->pool, "redirect:", r->filename, NULL);
            r->handler = "redirect-handler";
            return OK;
        }
    }
    else {
        rewritelog(r, 1, "[per-dir %s] pass through %s", 
                   dconf->directory, r->filename);
        return DECLINED;
    }
}