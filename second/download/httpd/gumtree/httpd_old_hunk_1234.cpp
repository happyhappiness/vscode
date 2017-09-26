                                  "Error reading from remote server");
        }
        if (rc != 229 && rc != 500 && rc != 501 && rc != 502) {
            return ftp_proxyerror(r, backend, HTTP_BAD_GATEWAY, ftpmessage);
        }
        else if (rc == 229) {
            char *pstr;
            char *tok_cntx;

            pstr = ftpmessage;
            pstr = apr_strtok(pstr, " ", &tok_cntx);    /* separate result code */
            if (pstr != NULL) {
                if (*(pstr + strlen(pstr) + 1) == '=') {
                    pstr += strlen(pstr) + 2;
                }
                else {
                    pstr = apr_strtok(NULL, "(", &tok_cntx);    /* separate address &
                                                                 * port params */
                    if (pstr != NULL)
                        pstr = apr_strtok(NULL, ")", &tok_cntx);
                }
            }

            if (pstr) {
                apr_sockaddr_t *epsv_addr;
                data_port = atoi(pstr + 3);

                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                       "proxy: FTP: EPSV contacting remote host on port %d",
                             data_port);

                if ((rv = apr_socket_create(&data_sock, connect_addr->family, SOCK_STREAM, 0, r->pool)) != APR_SUCCESS) {
