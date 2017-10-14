ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate CommonName (CN) `%s' "
                         "does NOT match server name!?",
                         ssl_asn1_keystr(type), cn);