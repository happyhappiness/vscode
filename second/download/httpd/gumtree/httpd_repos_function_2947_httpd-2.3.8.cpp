static void log_perms_failure(apr_status_t rv, server_rec *s, const char *type)
{
    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                 "Couldn't set permissions on the %s mutex; "
                 "check User and Group directives",
                 type);
}