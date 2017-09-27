    apr_status_t rv;

    rv = apr_socket_create(&ctx->sock, ctx->mcast_addr->family,
                           SOCK_DGRAM, APR_PROTO_UDP, ctx->p);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to create listening socket.");
        return rv;
    }

    rv = apr_socket_opt_set(ctx->sock, APR_SO_REUSEADDR, 1);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to set APR_SO_REUSEADDR to 1 on socket.");
        return rv;
    }


    rv = apr_socket_opt_set(ctx->sock, APR_SO_NONBLOCK, 1);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to set APR_SO_NONBLOCK to 1 on socket.");
        return rv;
    }

    rv = apr_socket_bind(ctx->sock, ctx->mcast_addr);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to bind on socket.");
        return rv;
    }

    rv = apr_mcast_join(ctx->sock, ctx->mcast_addr, NULL, NULL);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to join multicast group");
        return rv;
    }

    rv = apr_mcast_loopback(ctx->sock, 1);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                     "Heartmonitor: Failed to accept localhost mulitcast on socket.");
        return rv;
    }

    return APR_SUCCESS;
}

