    /*

     *  only do something under runtime if the engine is really enabled,

     *  for this directory, else return immediately!

     */

    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {

        /* FollowSymLinks is mandatory! */

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "

                     "which implies that RewriteRule directive is forbidden: "

                     "%s", r->filename);

        return FORBIDDEN;

    }

    else {

