
        if (!inf->x509 || !inf->x_pkey) {
            sk_X509_INFO_free(sk);
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s, APLOGNO(02252)
                         "incomplete client cert configured for SSL proxy "
                         "(missing or encrypted private key?)");
            ssl_die(s);
            return;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02207)
                 "loaded %d client certs for SSL proxy",
