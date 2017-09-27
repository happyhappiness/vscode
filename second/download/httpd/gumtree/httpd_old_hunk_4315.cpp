    while (apr_isspace(*strend))
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
