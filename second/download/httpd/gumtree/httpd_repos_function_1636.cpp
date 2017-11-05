static void hm_processmsg(hm_ctx_t *ctx, apr_pool_t *p,
                                  apr_sockaddr_t *from, char *buf, int len)
{
    apr_table_t *tbl;

    buf[len] = '\0';

    tbl = apr_table_make(p, 10);

    qs_to_table(buf, tbl, p);

    if (apr_table_get(tbl, "v") != NULL &&
        apr_table_get(tbl, "busy") != NULL &&
        apr_table_get(tbl, "ready") != NULL) {
        char *ip;
        int port = 80;
        hm_server_t *s;
        /* TODO: REMOVE ME BEFORE PRODUCTION (????) */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
                     "Heartmonitor: %pI busy=%s ready=%s", from,
                     apr_table_get(tbl, "busy"), apr_table_get(tbl, "ready"));

        apr_sockaddr_ip_get(&ip, from);

        if (apr_table_get(tbl, "port") != NULL)
            port = atoi(apr_table_get(tbl, "port"));
           
        s = hm_get_server(ctx, ip, port);

        s->busy = atoi(apr_table_get(tbl, "busy"));
        s->ready = atoi(apr_table_get(tbl, "ready"));
        s->seen = apr_time_now();
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ctx->s,
                     "Heartmonitor: malformed message from %pI",
                     from);
    }

}