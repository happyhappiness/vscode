    char *user = r->user;
    apr_table_t *grpstatus = NULL;
    apr_status_t status;
    const char *filegroup = NULL;

    if (!user) {
        return AUTHZ_DENIED_NO_USER;
    }

    /* If there is no group file - then we are not
     * configured. So decline.
     */
    if (!(conf->groupfile)) {
