    do {
        apr_status_t rv;
        rv = apr_socket_create(&sock, ctx->mcast_addr->family,
                               SOCK_DGRAM, APR_PROTO_UDP, p);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, APLOGNO(02097) "Heartbeat: apr_socket_create failed");
            break;
        }

        rv = apr_mcast_loopback(sock, 1);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, APLOGNO(02098) "Heartbeat: apr_mcast_loopback failed");
            break;
        }

        rv = apr_socket_sendto(sock, ctx->mcast_addr, 0, buf, &len);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, APLOGNO(02099) "Heartbeat: apr_socket_sendto failed");
            break;
        }
    } while (0);

    if (sock) {
        apr_socket_close(sock);
