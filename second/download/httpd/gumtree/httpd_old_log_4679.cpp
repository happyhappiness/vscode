ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "%s server certificate enables "
                     "Server Gated Cryptography (SGC)",
                     ssl_asn1_keystr(type));