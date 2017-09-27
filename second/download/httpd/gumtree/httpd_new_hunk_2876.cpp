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
