                return SSL_TLSEXT_ERR_NOACK;
            }
        }
    }

    if (rsp == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01954)
                     "stapling_cb: renewing cached response");
        rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, conn->pool);

        if (rv == FALSE) {
            stapling_mutex_off(s);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01955)
                         "stapling_cb: fatal error");
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        }
    }
    stapling_mutex_off(s);

    if (rsp) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01956)
                     "stapling_cb: setting response");
        if (!stapling_set_response(ssl, rsp))
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        return SSL_TLSEXT_ERR_OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01957)
                 "stapling_cb: no response available");

    return SSL_TLSEXT_ERR_NOACK;

}

