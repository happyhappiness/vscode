static void warn_if_non_blank(
    const char * what,
    char * ptr,
    ap_configfile_t * cfg)
{
    char * p;
    for (p=ptr; *p; p++) {
        if (*p == '#')
            break;
        if (*p != ' ' && *p != '\t') {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                         "%s on line %d of %s: %s",
                         what, cfg->line_number, cfg->name, ptr);
            break;
        }
    }
}