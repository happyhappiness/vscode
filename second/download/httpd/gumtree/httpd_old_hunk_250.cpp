            }

            if (pstr) {
                apr_sockaddr_t *epsv_addr;
                data_port = atoi(pstr + 3);

                ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                       "proxy: FTP: EPSV contacting remote host on port %d",
                             data_port);

                if ((rv = apr_socket_create(&data_sock, APR_INET, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: FTP: error creating EPSV socket");
