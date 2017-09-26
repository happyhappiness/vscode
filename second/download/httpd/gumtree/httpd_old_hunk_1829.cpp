        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
          "proxy: FTP: an error occurred creating the transfer connection");
        proxy_ftp_cleanup(r, backend);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* set up the connection filters */
    rc = ap_run_pre_connection(data, data_sock);
    if (rc != OK && rc != DONE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: pre_connection setup failed (%d)",
                     rc);
