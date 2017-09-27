        pfd.desc.s = lr->sd;
        pfd.reqevents = APR_POLLIN;
        pfd.client_data = lr;

        status = apr_pollset_add(pollset, &pfd);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf, APLOGNO(00157)
                         "Couldn't add listener to pollset; check system or user limits");
            clean_child_exit(APEXIT_CHILDSICK);
        }

        lr->accept_func = ap_unixd_accept;
    }
