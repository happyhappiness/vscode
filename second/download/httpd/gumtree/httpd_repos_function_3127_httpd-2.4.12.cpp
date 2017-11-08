static int update_child_status_internal(int child_num,
                                        int thread_num,
                                        int status,
                                        conn_rec *c,
                                        request_rec *r)
{
    int old_status;
    worker_score *ws;
    process_score *ps;
    int mpm_generation;

    ws = &ap_scoreboard_image->servers[child_num][thread_num];
    old_status = ws->status;
    ws->status = status;

    ps = &ap_scoreboard_image->parent[child_num];

    if (status == SERVER_READY
        && old_status == SERVER_STARTING) {
        ws->thread_num = child_num * thread_limit + thread_num;
        ap_mpm_query(AP_MPMQ_GENERATION, &mpm_generation);
        ps->generation = mpm_generation;
    }

    if (ap_extended_status) {
        ws->last_used = apr_time_now();
        if (status == SERVER_READY || status == SERVER_DEAD) {
            /*
             * Reset individual counters
             */
            if (status == SERVER_DEAD) {
                ws->my_access_count = 0L;
                ws->my_bytes_served = 0L;
            }
            ws->conn_count = 0;
            ws->conn_bytes = 0;
        }
        if (r) {
            const char *client = ap_get_remote_host(c, r->per_dir_config,
                                 REMOTE_NOLOOKUP, NULL);
            if (!client || !strcmp(client, c->client_ip)) {
                apr_cpystrn(ws->client, r->useragent_ip, sizeof(ws->client));
            }
            else {
                apr_cpystrn(ws->client, client, sizeof(ws->client));
            }
            copy_request(ws->request, sizeof(ws->request), r);
            if (r->server) {
                apr_snprintf(ws->vhost, sizeof(ws->vhost), "%s:%d",
                             r->server->server_hostname,
                             r->connection->local_addr->port);
            }
        }
        else if (c) {
            apr_cpystrn(ws->client, ap_get_remote_host(c, NULL,
                        REMOTE_NOLOOKUP, NULL), sizeof(ws->client));
            ws->request[0]='\0';
            ws->vhost[0]='\0';
        }
    }

    return old_status;
}