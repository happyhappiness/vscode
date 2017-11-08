static const char *log_env_var(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, apr_table_get(r->subprocess_env, a));
}