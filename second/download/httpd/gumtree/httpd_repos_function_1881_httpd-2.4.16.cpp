static int update_echo_child_status(ap_sb_handle_t *sbh,
                                    int status, conn_rec *c,
                                    apr_bucket_brigade *last_echoed)
{
    worker_score *ws = ap_get_scoreboard_worker(sbh);
    int old_status = ws->status;

    ws->status = status;

    if (!ap_extended_status)
        return old_status;

    ws->last_used = apr_time_now();

    /* initial pass only, please - in the name of efficiency */
    if (c) {
        apr_cpystrn(ws->client,
                    ap_get_remote_host(c, c->base_server->lookup_defaults,
                                       REMOTE_NOLOOKUP, NULL),
                    sizeof(ws->client));
        apr_cpystrn(ws->vhost, c->base_server->server_hostname,
                    sizeof(ws->vhost));
        /* Deliberate trailing space - filling in string on WRITE passes */
        apr_cpystrn(ws->request, "ECHO ", sizeof(ws->request));
    }

    /* each subsequent WRITE pass, let's update what we echoed */
    if (last_echoed) {
        brigade_peek(last_echoed, ws->request + sizeof("ECHO ") - 1,
                     sizeof(ws->request) - sizeof("ECHO ") + 1);
    }

    return old_status;
}