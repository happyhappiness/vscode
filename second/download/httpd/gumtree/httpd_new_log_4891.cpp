ssl_log_cxerror(SSLLOG_MARK, APLOG_DEBUG, 0, c, info->x509, APLOGNO(02277)
                    SSLPROXY_CERT_CB_LOG_FMT "%s, sending",
                    (mySrvConfigFromConn(c))->vhost_id, msg);