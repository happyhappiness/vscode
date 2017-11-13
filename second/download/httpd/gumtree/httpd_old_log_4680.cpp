ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate is a CA certificate "
                         "(BasicConstraints: CA == TRUE !?)",
                         ssl_asn1_keystr(type));