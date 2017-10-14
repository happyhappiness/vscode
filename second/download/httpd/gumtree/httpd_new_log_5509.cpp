ap_log_error(APLOG_MARK, APLOG_NOTICE|APLOG_STARTUP, APR_SUCCESS, NULL, APLOGNO(00548)
                     "NameVirtualHost has no effect and will be removed in the "
                     "next release %s:%d",
                     cmd->directive->filename,
                     cmd->directive->line_num);