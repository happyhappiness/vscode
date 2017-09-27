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
        rewritelog((r, 2, dconf->directory, "init rewrite engine with"
                   " requested uri %s", r->filename));
    }
