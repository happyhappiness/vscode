        return 1;
    }

    if (is_graceful) {
        char char_of_death = '!';

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0,
                     ap_server_conf, AP_SIG_GRACEFUL_STRING " received.  "
                     "Doing graceful restart");

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */
