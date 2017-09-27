            stapling_refresh_mutex_off(s);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_cb: still must refresh cached response "
                         "after obtaining refresh mutex");
            rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, conn->pool);
            stapling_refresh_mutex_off(s);

            if (rv == TRUE) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "stapling_cb: success renewing response");
            }
