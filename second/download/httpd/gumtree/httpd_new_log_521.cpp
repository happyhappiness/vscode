ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile]");