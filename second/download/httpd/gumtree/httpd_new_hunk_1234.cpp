                                  "Error reading from remote server");
        }
        if (rc != 229 && rc != 500 && rc != 501 && rc != 502) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }
        else if (rc == 229) {
            /* Parse the port out of the EPSV reply. */
            data_port = parse_epsv_reply(ftpmessage);

            if (data_port) {
                apr_sockaddr_t *epsv_addr;

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                       "proxy: FTP: EPSV contacting remote host on port %d",
                             data_port);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
