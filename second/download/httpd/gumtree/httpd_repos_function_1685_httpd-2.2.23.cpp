static const char *add_include_vars_lazy(request_rec *r, const char *var, const char *timefmt)
{
    char *val;
    if (!strcasecmp(var, "DATE_LOCAL")) {
        val = ap_ht_time(r->pool, r->request_time, timefmt, 0);
    }
    else if (!strcasecmp(var, "DATE_GMT")) {
        val = ap_ht_time(r->pool, r->request_time, timefmt, 1);
    }
    else if (!strcasecmp(var, "LAST_MODIFIED")) {
        val = ap_ht_time(r->pool, r->finfo.mtime, timefmt, 0);
    }
    else if (!strcasecmp(var, "USER_NAME")) {
        if (apr_uid_name_get(&val, r->finfo.user, r->pool) != APR_SUCCESS) {
            val = "<unknown>";
        }
    }
    else {
        val = NULL;
    }

    if (val) {
        apr_table_setn(r->subprocess_env, var, val);
    }
    return val;
}