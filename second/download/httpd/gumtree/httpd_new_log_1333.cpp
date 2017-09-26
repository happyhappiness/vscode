ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
#ifdef OPENSSL_NO_TLSEXT
                     "Init: You should not use name-based "
                     "virtual hosts in conjunction with SSL!!");