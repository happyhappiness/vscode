{
    char * p;
    for (p=ptr; *p; p++) {
        if (*p == '#')
            break;
        if (*p != ' ' && *p != '\t') {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(02989)
                         "%s on line %d of %s: %s",
                         what, cfg->line_number, cfg->name, ptr);
            break;
        }
    }
}
