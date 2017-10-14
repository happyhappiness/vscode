static void log_unknown_type(server_rec *s, const char *type)
{
    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                 "Can't create mutex of unknown type %s", type);
}