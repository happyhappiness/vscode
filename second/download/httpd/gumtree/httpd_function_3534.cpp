static int hb_monitor(hb_ctx_t *ctx, apr_pool_t *p)
{
    apr_size_t len;
    apr_socket_t *sock = NULL;
    char buf[256];
    int i, j;
    apr_uint32_t ready = 0;
    apr_uint32_t busy = 0;
    ap_generation_t mpm_generation;

    ap_mpm_query(AP_MPMQ_GENERATION, &mpm_generation);

    for (i = 0; i < ctx->server_limit; i++) {
        process_score *ps;
        ps = ap_get_scoreboard_process(i);

        for (j = 0; j < ctx->thread_limit; j++) {
            int res;

            worker_score *ws = NULL;

            ws = &ap_scoreboard_image->servers[i][j];

            res = ws->status;

            if (res == SERVER_READY && ps->generation == mpm_generation) {
                ready++;
            }
            else if (res != SERVER_DEAD &&
                     res != SERVER_STARTING && res != SERVER_IDLE_KILL &&
                     ps->generation == mpm_generation) {
                busy++;
            }
        }
    }

    len = apr_snprintf(buf, sizeof(buf), msg_format, MSG_VERSION, ready, busy);

    do {
        apr_status_t rv;
        rv = apr_socket_create(&sock, ctx->mcast_addr->family,
                               SOCK_DGRAM, APR_PROTO_UDP, p);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, "Heartbeat: apr_socket_create failed");
            break;
        }

        rv = apr_mcast_loopback(sock, 1);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, "Heartbeat: apr_mcast_loopback failed");
            break;
        }

        rv = apr_socket_sendto(sock, ctx->mcast_addr, 0, buf, &len);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv,
                         NULL, "Heartbeat: apr_socket_sendto failed");
            break;
        }
    } while (0);

    if (sock) {
        apr_socket_close(sock);
    }

    return OK;
}