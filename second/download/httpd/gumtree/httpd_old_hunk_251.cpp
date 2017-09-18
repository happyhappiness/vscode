
            if (pstr != NULL && (sscanf(pstr,
                 "%d,%d,%d,%d,%d,%d", &h3, &h2, &h1, &h0, &p1, &p0) == 6)) {

                apr_sockaddr_t *pasv_addr;
                apr_port_t pasvport = (p1 << 8) + p0;
                ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                          "proxy: FTP: PASV contacting host %d.%d.%d.%d:%d",
                             h3, h2, h1, h0, pasvport);

                if ((rv = apr_socket_create(&data_sock, APR_INET, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "proxy: error creating PASV socket");
