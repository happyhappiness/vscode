        if (response_status == OCSP_RESPONSE_STATUS_SUCCESSFUL) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01942)
                        "stapling_renew_response: query response received");
            stapling_check_response(s, mctx, cinf, *prsp, &ok);
            if (ok == FALSE) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01943)
                             "stapling_renew_response: error in retrieved response!");
            }
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01944)
                         "stapling_renew_response: responder error %s",
                         OCSP_response_status_str(response_status));
