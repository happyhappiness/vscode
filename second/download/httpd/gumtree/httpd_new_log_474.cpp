ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "SSL cipher suite not renegotiated: "
                             "access to %s denied using cipher %s",
                              r->filename,
                              SSL_CIPHER_get_name(cipher));