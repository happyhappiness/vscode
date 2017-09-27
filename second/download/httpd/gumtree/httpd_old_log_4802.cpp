ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
#ifndef OPENSSL_NO_EC
                "Oops, no RSA, DSA or ECC server certificate found "
#else
                "Oops, no RSA or DSA server certificate found "
#endif
                "for '%s:%d'?!", s->server_hostname, s->port);