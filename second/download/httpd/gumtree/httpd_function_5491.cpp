static void log_bad_create_options(server_rec *s, const char *type)
{
    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                 "Invalid options were specified when creating the %s mutex",
                 type);
}