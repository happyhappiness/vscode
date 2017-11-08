static const char *header_request_env_var(request_rec *r, char *a)
{
    const char *s = apr_table_get(r->subprocess_env,a);

    if (s)
        return unwrap_header(r->pool, s);
    else
        return "(null)";
}