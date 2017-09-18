    else {
        /* sconf is the server config for this vhost, so if our socket
         * is not the same that was set in the config, then the request
         * needs to be passed to another child. */
        if (sconf->sd != child_info_table[child_num].sd) {
            if (pass_request(r) == -1) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             ap_server_conf, "Could not pass request to proper "
                             "child, request will not be honored.");
            }
            longjmp(jmpbuffer, 1); 
        }
        return OK;
