static char *expand_tildepaths(request_rec *r, char *uri)
{
    char user[LONG_STRING_LEN];
    char *newuri;
    int i, j;
    char *homedir;

    newuri = uri;
    if (uri != NULL && strlen(uri) > 2 && uri[0] == '/' && uri[1] == '~') {
        /* cut out the username */
        for (j = 0, i = 2; j < sizeof(user)-1
               && uri[i] != '\0'
               && uri[i] != '/'  ; ) {
            user[j++] = uri[i++];
        }
        user[j] = '\0';

        /* lookup username in systems passwd file */
        if (apr_get_home_directory(&homedir, user, r->pool) == APR_SUCCESS) {
            /* ok, user was found, so expand the ~user string */
            if (uri[i] != '\0') {
                /* ~user/anything...  has to be expanded */
                if (homedir[strlen(homedir)-1] == '/') {
                    homedir[strlen(homedir)-1] = '\0';
                }
                newuri = apr_pstrcat(r->pool, homedir, uri+i, NULL);
            }
            else {
                /* only ~user has to be expanded */
                newuri = homedir;
            }
        }
    }
    return newuri;
}