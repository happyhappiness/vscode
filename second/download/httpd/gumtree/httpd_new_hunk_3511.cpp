    while (*strend && apr_isspace(*strend))
        ++strend;
    *line = strend;
    return res;
}

AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp)
{
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(00551)
        "Done with config file %s", cfp->name);
#endif
    return (cfp->close == NULL) ? 0 : cfp->close(cfp->param);
}

/* we can't use apr_file_* directly because of linking issues on Windows */
static apr_status_t cfg_close(void *param)
{
    return apr_file_close(param);
}

static apr_status_t cfg_getch(char *ch, void *param)
{
    return apr_file_getc(ch, param);
}

static apr_status_t cfg_getstr(void *buf, apr_size_t bufsiz, void *param)
{
    return apr_file_gets(buf, bufsiz, param);
}

/* Open a ap_configfile_t as FILE, return open ap_configfile_t struct pointer */
AP_DECLARE(apr_status_t) ap_pcfg_openfile(ap_configfile_t **ret_cfg,
                                          apr_pool_t *p, const char *name)
{
