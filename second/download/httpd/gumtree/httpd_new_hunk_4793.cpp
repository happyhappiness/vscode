                            sizeof(szPath));
                if ((rv = exists_and_readable(szPath, p, NULL))
                    != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02201)
                                 "Init: Can't open server certificate file %s",
                                 szPath);
                    ssl_die(s);
                }
                if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02241)
                                 "Init: Unable to read server certificate from"
                                 " file %s", szPath);
                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                    ssl_die(s);
                }
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02202)
                             "Init: Read server certificate from '%s'",
                             szPath);
            }
            /*
