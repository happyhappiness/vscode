    char *user = r->user;
    const char *t, *w;
    apr_table_t *grpstatus = NULL;
    apr_status_t status;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
