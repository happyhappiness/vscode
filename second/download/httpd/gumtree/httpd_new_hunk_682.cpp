    if (!connect) {
        apr_sockaddr_t *local_addr;
        char *local_ip;
        apr_port_t local_port;
        unsigned int h0, h1, h2, h3, p0, p1;

        if ((rv = apr_socket_create(&local_sock, connect_addr->family, SOCK_STREAM, r->pool)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FTP: error creating local socket");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_socket_addr_get(&local_addr, APR_LOCAL, sock);
        apr_sockaddr_port_get(&local_port, local_addr);
        apr_sockaddr_ip_get(&local_ip, local_addr);

        if ((rv = apr_socket_opt_set(local_sock, APR_SO_REUSEADDR, one)) 
                != APR_SUCCESS) {
#ifndef _OSD_POSIX              /* BS2000 has this option "always on" */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: FTP: error setting reuseaddr option");
            return HTTP_INTERNAL_SERVER_ERROR;
#endif                          /* _OSD_POSIX */
        }
