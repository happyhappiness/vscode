static char *expand_tildepaths(request_rec *r, char *uri)
{
    if (uri && *uri == '/' && uri[1] == '~') {
        char *p, *user;

        p = user = uri + 2;
        while (*p && *p != '/') {
            ++p;
        }

        if (p > user) {
            char *homedir;

            user = apr_pstrmemdup(r->pool, user, p-user);
            if (apr_uid_homepath_get(&homedir, user, r->pool) == APR_SUCCESS) {
                if (*p) {
                    /* reuse of user variable */
                    user = homedir + strlen(homedir) - 1;
                    if (user >= homedir && *user == '/') {
                        *user = '\0';
                    }

                    return apr_pstrcat(r->pool, homedir, p, NULL);
                }
                else {
                    return homedir;
                }
            }
        }
    }

    return uri;
}