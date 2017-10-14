ssl_log_xerror(SSLLOG_MARK, APLOG_ERR, 0, ptemp, s, x,
                       APLOGNO(02218) "ssl_stapling_init_cert: no OCSP URI "
                       "in certificate and no SSLStaplingForceURL set");