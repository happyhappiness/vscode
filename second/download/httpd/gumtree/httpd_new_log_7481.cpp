ap_log_error(APLOG_MARK, APLOG_WARNING|APLOG_STARTUP, 0, cmd->server,
                 APLOGNO(02559)
                 "The SSLCertificateChainFile directive (%s:%d) is deprecated, "
                 "SSLCertificateFile should be used instead",
                 cmd->directive->filename, cmd->directive->line_num);