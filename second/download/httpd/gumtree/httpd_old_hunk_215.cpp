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
