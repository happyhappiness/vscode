static unsigned int __stdcall worker_main(void *thread_num_val)
{
    static int requests_this_child = 0;
    winnt_conn_ctx_t *context = NULL;
    int thread_num = (int)thread_num_val;
    ap_sb_handle_t *sbh;
    apr_bucket *e;
    int rc;
    conn_rec *c;
    apr_int32_t disconnected;

    while (1) {

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

        /* Grab a connection off the network */
        context = winnt_get_connection(context);

        if (!context) {
            /* Time for the thread to exit */
            break;
        }

        /* Have we hit MaxRequestsPerChild connections? */
        if (ap_max_requests_per_child) {
            requests_this_child++;
            if (requests_this_child > ap_max_requests_per_child) {
                SetEvent(max_requests_per_child_event);
            }
        }

        e = context->overlapped.Pointer;

        ap_create_sb_handle(&sbh, context->ptrans, 0, thread_num);
        c = ap_run_create_connection(context->ptrans, ap_server_conf,
                                     context->sock, thread_num, sbh,
                                     context->ba);

        if (!c)
        {
            /* ap_run_create_connection closes the socket on failure */
            context->accept_socket = INVALID_SOCKET;
            if (e)
                apr_bucket_free(e);
            continue;
        }

        /* follow ap_process_connection(c, context->sock) logic
         * as it left us no chance to reinject our first data bucket.
         */
        ap_update_vhost_given_ip(c);

        rc = ap_run_pre_connection(c, context->sock);
        if (rc != OK && rc != DONE) {
            c->aborted = 1;
        }

        if (e && c->aborted)
        {
            apr_bucket_free(e);
        }
        else if (e)
        {
            core_ctx_t *ctx;
            core_net_rec *net;
            ap_filter_t *filt;

            filt = c->input_filters;
            while ((strcmp(filt->frec->name, "core_in") != 0) && filt->next)
                filt = filt->next;
            net = filt->ctx;
            ctx = net->in_ctx;

            if (net->in_ctx)
                ctx = net->in_ctx;
            else
            {
                ctx = apr_pcalloc(c->pool, sizeof(*ctx));
                ctx->b = apr_brigade_create(c->pool, c->bucket_alloc);
                ctx->tmpbb = apr_brigade_create(c->pool, c->bucket_alloc);

                /* seed the brigade with AcceptEx read heap bucket */
                e = context->overlapped.Pointer;
                APR_BRIGADE_INSERT_HEAD(ctx->b, e);

                /* also seed the brigade with the client socket. */
                e = apr_bucket_socket_create(net->client_socket,
                                             c->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(ctx->b, e);
                net->in_ctx = ctx;
            }
        }

        if (!c->aborted)
        {
            ap_run_process_connection(c);

            apr_socket_opt_get(context->sock, APR_SO_DISCONNECTED,
                               &disconnected);

            if (!disconnected) {
                context->accept_socket = INVALID_SOCKET;
                ap_lingering_close(c);
            }
        }
    }

    ap_update_child_status_from_indexes(0, thread_num, SERVER_DEAD,
                                        (request_rec *) NULL);

    return 0;
}