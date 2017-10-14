static const char *h2_conf_set_session_extra_files(cmd_parms *parms,
                                                   void *arg, const char *value)
{
    /* deprecated, ignore */
    (void)arg;
    (void)value;
    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->pool, /* NO LOGNO */
                  "H2SessionExtraFiles is obsolete and will be ignored");
    return NULL;
}