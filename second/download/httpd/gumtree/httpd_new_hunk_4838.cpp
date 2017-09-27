}

/**
 * Get the auth username and password from the main request
 * notes table, if present.
 */
static void get_notes_auth(request_rec *r,
                           const char **user, const char **pw,
                           const char **method, const char **mimetype)
{
    const char *authname;
    request_rec *m = r;

    /* find the main request */
    while (m->main) {
        m = m->main;
    }
    /* find the first redirect */
    while (m->prev) {
        m = m->prev;
    }

    /* have we isolated the user and pw before? */
    authname = ap_auth_name(m);
    if (user) {
        *user = (char *) apr_table_get(m->notes, apr_pstrcat(m->pool, authname, "-user", NULL));
    }
    if (pw) {
        *pw = (char *) apr_table_get(m->notes, apr_pstrcat(m->pool, authname, "-pw", NULL));
    }
    if (method) {
        *method = (char *) apr_table_get(m->notes, apr_pstrcat(m->pool, authname, "-method", NULL));
    }
    if (mimetype) {
        *mimetype = (char *) apr_table_get(m->notes, apr_pstrcat(m->pool, authname, "-mimetype", NULL));
    }

    /* set the user, even though the user is unauthenticated at this point */
    if (user && *user) {
        r->user = (char *) *user;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, r,
                  "from notes: user: %s, pw: %s, method: %s, mimetype: %s",
                  user ? *user : "<null>", pw ? *pw : "<null>",
                  method ? *method : "<null>", mimetype ? *mimetype : "<null>");
