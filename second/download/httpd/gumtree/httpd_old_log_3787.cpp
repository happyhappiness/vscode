ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, data->r,
                          "poll failed waiting for CGI child");