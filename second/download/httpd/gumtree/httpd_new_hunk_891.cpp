    *ret_cfg = new_cfg;
    return APR_SUCCESS;
}


/* Allocate a ap_configfile_t handle with user defined functions and params */
AP_DECLARE(ap_configfile_t *) ap_pcfg_open_custom(apr_pool_t *p,
                       const char *descr,
                       void *param,
                       int(*getch)(void *param),
                       void *(*getstr) (void *buf, size_t bufsiz, void *param),
                       int(*close_func)(void *param))
{
    ap_configfile_t *new_cfg = apr_palloc(p, sizeof(*new_cfg));
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "Opening config handler %s", descr);
#endif
    new_cfg->param = param;
    new_cfg->name = descr;
    new_cfg->getch = getch;
    new_cfg->getstr = getstr;
    new_cfg->close = close_func;
