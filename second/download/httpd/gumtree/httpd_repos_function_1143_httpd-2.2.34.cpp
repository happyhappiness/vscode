static int translate_userdir(request_rec *r)
{
    ap_conf_vector_t *server_conf;
    const userdir_config *s_cfg;
    char *name = r->uri;
    const char *userdirs;
    const char *w, *dname;
    char *redirect;
    apr_finfo_t statbuf;

    /*
     * If the URI doesn't match our basic pattern, we've nothing to do with
     * it.
     */
    if (name[0] != '/' || name[1] != '~') {
        return DECLINED;
    }
    server_conf = r->server->module_config;
    s_cfg = ap_get_module_config(server_conf, &userdir_module);
    userdirs = s_cfg->userdir;
    if (userdirs == NULL) {
        return DECLINED;
    }

    dname = name + 2;
    w = ap_getword(r->pool, &dname, '/');

    /*
     * The 'dname' funny business involves backing it up to capture the '/'
     * delimiting the "/~user" part from the rest of the URL, in case there
     * was one (the case where there wasn't being just "GET /~user HTTP/1.0",
     * for which we don't want to tack on a '/' onto the filename).
     */

    if (dname[-1] == '/') {
        --dname;
    }

    /*
     * If there's no username, it's not for us.  Ignore . and .. as well.
     */
    if (w[0] == '\0' || (w[1] == '.' && (w[2] == '\0' || (w[2] == '.' && w[3] == '\0')))) {
        return DECLINED;
    }
    /*
     * Nor if there's an username but it's in the disabled list.
     */
    if (apr_table_get(s_cfg->disabled_users, w) != NULL) {
        return DECLINED;
    }
    /*
     * If there's a global interdiction on UserDirs, check to see if this
     * name is one of the Blessed.
     */
    if (s_cfg->globally_disabled == O_DISABLE
        && apr_table_get(s_cfg->enabled_users, w) == NULL) {
        return DECLINED;
    }

    /*
     * Special cases all checked, onward to normal substitution processing.
     */

    while (*userdirs) {
        const char *userdir = ap_getword_conf(r->pool, &userdirs);
        char *filename = NULL, *x = NULL;
        apr_status_t rv;
        int is_absolute = ap_os_is_path_absolute(r->pool, userdir);

        if (ap_strchr_c(userdir, '*'))
            x = ap_getword(r->pool, &userdir, '*');

        if (userdir[0] == '\0' || is_absolute) {
            if (x) {
#ifdef HAVE_DRIVE_LETTERS
                /*
                 * Crummy hack. Need to figure out whether we have been
                 * redirected to a URL or to a file on some drive. Since I
                 * know of no protocols that are a single letter, ignore
                 * a : as the first or second character, and assume a file
                 * was specified
                 */
                if (strchr(x + 2, ':'))
#else
                if (strchr(x, ':') && !is_absolute)
#endif /* HAVE_DRIVE_LETTERS */
                {
                    redirect = apr_pstrcat(r->pool, x, w, userdir, dname, NULL);
                    apr_table_setn(r->headers_out, "Location", redirect);
                    return HTTP_MOVED_TEMPORARILY;
                }
                else
                    filename = apr_pstrcat(r->pool, x, w, userdir, NULL);
            }
            else
                filename = apr_pstrcat(r->pool, userdir, "/", w, NULL);
        }
        else if (x && ap_strchr_c(x, ':')) {
            redirect = apr_pstrcat(r->pool, x, w, dname, NULL);
            apr_table_setn(r->headers_out, "Location", redirect);
            return HTTP_MOVED_TEMPORARILY;
        }
        else {
#if APR_HAS_USER
            char *homedir;

            if (apr_uid_homepath_get(&homedir, w, r->pool) == APR_SUCCESS) {
                filename = apr_pstrcat(r->pool, homedir, "/", userdir, NULL);
            }
#else
            return DECLINED;
#endif
        }

        /*
         * Now see if it exists, or we're at the last entry. If we are at the
         * last entry, then use the filename generated (if there is one)
         * anyway, in the hope that some handler might handle it. This can be
         * used, for example, to run a CGI script for the user.
         */
        if (filename && (!*userdirs
                      || ((rv = apr_stat(&statbuf, filename, APR_FINFO_MIN,
                                         r->pool)) == APR_SUCCESS
                                             || rv == APR_INCOMPLETE))) {
            r->filename = apr_pstrcat(r->pool, filename, dname, NULL);
            /* XXX: Does this walk us around FollowSymLink rules?
             * When statbuf contains info on r->filename we can save a syscall
             * by copying it to r->finfo
             */
            if (*userdirs && dname[0] == 0)
                r->finfo = statbuf;

            /* For use in the get_suexec_identity phase */
            apr_table_setn(r->notes, "mod_userdir_user", w);

            return OK;
        }
    }

    return DECLINED;
}