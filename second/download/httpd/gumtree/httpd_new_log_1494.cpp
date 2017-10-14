ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "loaded %i intermediate CA%s for cert %i (%s)",
                         i, i == 1 ? "" : "s", n, cert_dn);