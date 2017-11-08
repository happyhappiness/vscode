static DWORD __stdcall worker_main(void *thread_num_val)
{
    apr_thread_t *thd = NULL;
    apr_os_thread_t osthd;
    static int requests_this_child = 0;
    winnt_conn_ctx_t *context = NULL;
    int thread_num = (int)thread_num_val;
    ap_sb_handle_t *sbh;
    apr_bucket *e;
    int rc;
    conn_rec *c;
    apr_int32_t disconnected;

    osthd = apr_os_thread_current();
    apr_os_thread_put(&thd, &osthd, pchild);

    while (1) {

        ap_update_child_status_from_indexes(0, thread_num, SERVER_READY, NULL);

        /* Grab a connection off the network */
        context = winnt_get_connection(context);

        if (!context) {
            /* Time for the thread to exit */
            break;
        }

        /* Have we hit MaxConnectionsPerChild connections? */
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

        c->current_thread = thd;

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
        else
        {
            ap_set_module_config(c->conn_config, &mpm_winnt_module, context);
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