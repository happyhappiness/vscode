ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
                             "[%s] modssl_X509_match_name: expecting name '%s', "
                             "%smatched by ID '%s'",
                             (mySrvConfig(s))->vhost_id, name,
                             matched == TRUE ? "" : "NOT ", id[i]);