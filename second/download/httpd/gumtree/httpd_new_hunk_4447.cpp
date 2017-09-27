        rewritelog((r, 8, dconf->directory, "Declining, no further rewriting due to END flag"));
        return DECLINED;
    }

    /*
     *  Do the Options check after engine check, so
     *  the user is able to explicitly turn RewriteEngine Off.
     */
    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
        /* FollowSymLinks is mandatory! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00670)
                     "Options FollowSymLinks and SymLinksIfOwnerMatch are both off, "
                     "so the RewriteRule directive is also forbidden "
