ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02240)
                         "Server should be SSL-aware but has no certificate "
                         "configured [Hint: SSLCertificateFile] (%s:%d)",
                         pServ->defn_name, pServ->defn_line_number);