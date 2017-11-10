static apr_status_t get_dbm_grp(request_rec *r, char *key1, char *key2,
                                char *dbmgrpfile, char *dbtype,
                                const char ** out)
{
    char *grp_colon, *val;
    apr_status_t retval;
    apr_dbm_t *f;

    retval = apr_dbm_open_ex(&f, dbtype, dbmgrpfile, APR_DBM_READONLY,
                             APR_OS_DEFAULT, r->pool);

    if (retval != APR_SUCCESS) {
        return retval;
    }

    /* Try key2 only if key1 failed */
    if (!(val = get_dbm_entry_as_str(r->pool, f, key1))) {
        val = get_dbm_entry_as_str(r->pool, f, key2);
    }

    apr_dbm_close(f);

    if (val && (grp_colon = ap_strchr(val, ':')) != NULL) {
        char *grp_colon2 = ap_strchr(++grp_colon, ':');

        if (grp_colon2) {
            *grp_colon2 = '\0';
        }
        *out = grp_colon;
    }
    else {
        *out = val;
    }

    return retval;
}