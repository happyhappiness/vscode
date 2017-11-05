ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01793)
                          "invalid qop `%s' received: %s",
                          resp->message_qop, r->uri);