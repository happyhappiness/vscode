
static const char *set_cookie_log(cmd_parms *cmd, void *dummy, const char *fn)
{
    return add_custom_log(cmd, dummy, fn, "%{Cookie}n \"%r\" %t", NULL);
}

static const char *set_buffered_logs_on(cmd_parms *parms, void *dummy, int flag)
{
    buffered_logs = flag;
    ap_log_set_writer_init(ap_buffered_log_writer_init);
    ap_log_set_writer(ap_buffered_log_writer);
    return NULL;
}
static const command_rec config_log_cmds[] =
{
AP_INIT_TAKE23("CustomLog", add_custom_log, NULL, RSRC_CONF,
     "a file name, a custom log format string or format name, "
     "and an optional \"env=\" clause (see docs)"),
AP_INIT_TAKE1("TransferLog", set_transfer_log, NULL, RSRC_CONF,
     "the filename of the access log"),
AP_INIT_TAKE12("LogFormat", log_format, NULL, RSRC_CONF,
     "a log format string (see docs) and an optional format name"),
AP_INIT_TAKE1("CookieLog", set_cookie_log, NULL, RSRC_CONF,
     "the filename of the cookie log"),
AP_INIT_FLAG("BufferedLogs", set_buffered_logs_on, NULL, RSRC_CONF,
                 "Enable Buffered Logging (experimental)"),
    {NULL}
};

static config_log_state *open_config_log(server_rec *s, apr_pool_t *p,
                                         config_log_state *cls,
                                         apr_array_header_t *default_format)
{
    if (cls->log_writer != NULL) {
        return cls;             /* virtual config shared w/main server */
    }

    if (cls->fname == NULL) {
        return cls;             /* Leave it NULL to decline.  */
    }
    
    cls->log_writer = log_writer_init(p, s, cls->fname);
    if (cls->log_writer == NULL)
        return NULL; 

    return cls;
}

static int open_multi_logs(server_rec *s, apr_pool_t *p)
{
    int i;
    multi_log_state *mls = ap_get_module_config(s->module_config,
                                             &log_config_module);
    config_log_state *clsarray;
    const char *dummy;
