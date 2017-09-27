        ret = SSLize_Socket(sockdes, key, r);
        if (!ret) {
            csd_data->is_secure = 1;
        }
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "Upgradeable socket handle not found");
        return AP_FILTER_ERROR;
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                 "Awaiting re-negotiation handshake");

    /* Now that we have initialized the ssl connection which added the ssl_io_filter,
       pass the brigade off to the connection based output filters so that the
       request can complete encrypted */
    return ap_pass_brigade(f->c->output_filters, bb);
