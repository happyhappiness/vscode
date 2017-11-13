ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01944)
                         "stapling_renew_response: responder error %s",
                         OCSP_response_status_str(response_status));