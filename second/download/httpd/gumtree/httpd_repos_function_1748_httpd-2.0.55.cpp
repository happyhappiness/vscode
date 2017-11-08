static char *get_dbm_pw(request_rec *r, 
                        char *user, 
                        char *auth_dbmpwfile, 
                        char *dbtype)
{
    apr_dbm_t *f;
    apr_datum_t d, q;
    char *pw = NULL;
    apr_status_t retval;
    q.dptr = user;
#ifndef NETSCAPE_DBM_COMPAT
    q.dsize = strlen(q.dptr);
#else
    q.dsize = strlen(q.dptr) + 1;
#endif

    retval = apr_dbm_open_ex(&f, dbtype, auth_dbmpwfile, APR_DBM_READONLY, 
                             APR_OS_DEFAULT, r->pool);
    if (retval != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, retval, r,
                      "could not open dbm (type %s) auth file: %s", dbtype, 
                      auth_dbmpwfile);
        return NULL;
    }
    if (apr_dbm_fetch(f, q, &d) == APR_SUCCESS && d.dptr) {
        pw = apr_palloc(r->pool, d.dsize + 1);
        strncpy(pw, d.dptr, d.dsize);
        pw[d.dsize] = '\0'; /* Terminate the string */
    }

    apr_dbm_close(f);
    return pw;
}