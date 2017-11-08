static int fix_auth_header(void *vr, const char *key, const char *val)
{
    request_rec *r = vr;

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "moving %s->%s", key, val);
    apr_table_unset(r->err_headers_out, key);
    apr_table_setn(r->subprocess_env, key + 9, val);
    return 1;
}