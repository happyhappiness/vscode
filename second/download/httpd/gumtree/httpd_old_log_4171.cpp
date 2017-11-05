ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         ssl_asn1_keystr(type), pathlen);