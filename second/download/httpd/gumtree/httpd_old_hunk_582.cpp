    int(*getch)(void *param),
    void *(*getstr) (void *buf, size_t bufsiz, void *param),
    int(*close_func)(void *param))
{
    ap_configfile_t *new_cfg = apr_palloc(p, sizeof(*new_cfg));
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, NULL, "Opening config handler %s", descr);
#endif
    new_cfg->param = param;
    new_cfg->name = descr;
    new_cfg->getch = getch;
    new_cfg->getstr = getstr;
    new_cfg->close = close_func;
