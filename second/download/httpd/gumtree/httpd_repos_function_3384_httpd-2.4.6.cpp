static void log_create_failure(apr_status_t rv, server_rec *s, const char *type,
                               const char *fname)
{
    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00023)
                 "Couldn't create the %s mutex %s%s%s", type,
                 fname ? "(file " : "",
                 fname ? fname : "",
                 fname ? ")" : "");
}