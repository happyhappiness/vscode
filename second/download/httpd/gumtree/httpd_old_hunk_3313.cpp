        apr_socket_opt_set(pfd->desc.s, APR_SO_NONBLOCK, 1);
        apr_pollset_add(event_pollset, pfd);

        lr->accept_func = ap_unixd_accept;
    }

#if HAVE_SERF
    baton = apr_pcalloc(p, sizeof(*baton));
    baton->pollset = event_pollset;
    /* TODO: subpools, threads, reuse, etc.  -- currently use malloc() inside :( */
    baton->pool = p;

    g_serf = serf_context_create_ex(baton,
                                    s_socket_add,
                                    s_socket_remove, p);

    ap_register_provider(p, "mpm_serf",
                         "instance", "0", g_serf);

#endif

    return APR_SUCCESS;
}

static apr_status_t push_timer2worker(timer_event_t* te)
{
    return ap_queue_push_timer(worker_queue, te);
}

static apr_status_t push2worker(const apr_pollfd_t * pfd,
                                apr_pollset_t * pollset)
{
    listener_poll_type *pt = (listener_poll_type *) pfd->client_data;
    conn_state_t *cs = (conn_state_t *) pt->baton;
    apr_status_t rc;

    if (pt->bypass_push) {
        return APR_SUCCESS;
    }

    pt->bypass_push = 1;

    rc = apr_pollset_remove(pollset, pfd);

    /*
     * Some of the pollset backends, like KQueue or Epoll
     * automagically remove the FD if the socket is closed,
     * therefore, we can accept _SUCCESS or _NOTFOUND,
     * and we still want to keep going
     */
    if (rc != APR_SUCCESS && !APR_STATUS_IS_NOTFOUND(rc)) {
        cs->state = CONN_STATE_LINGER;
    }

    rc = ap_queue_push(worker_queue, cs->pfd.desc.s, cs, cs->p);
    if (rc != APR_SUCCESS) {
        /* trash the connection; we couldn't queue the connected
         * socket to a worker
         */
        apr_bucket_alloc_destroy(cs->bucket_alloc);
        apr_socket_close(cs->pfd.desc.s);
        ap_log_error(APLOG_MARK, APLOG_CRIT, rc,
                     ap_server_conf, "push2worker: ap_queue_push failed");
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
    }

    return rc;
}

/* get_worker:
 *     reserve a worker thread, block if all are currently busy.
 *     this prevents the worker queue from overflowing and lets
 *     other processes accept new connections in the mean time.
 */
static int get_worker(int *have_idle_worker_p)
{
    apr_status_t rc;

    if (!*have_idle_worker_p) {
        rc = ap_queue_info_wait_for_idler(worker_queue_info);

        if (rc == APR_SUCCESS) {
            *have_idle_worker_p = 1;
            return 1;
        }
        else {
            if (!APR_STATUS_IS_EOF(rc)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                             "ap_queue_info_wait_for_idler failed.  "
                             "Attempting to shutdown process gracefully");
                signal_threads(ST_GRACEFUL);
            }
            return 0;
        }
    }
    else {
        /* already reserved a worker thread - must have hit a
         * transient error on a previous pass
         */
        return 1;
    }
}

/* XXXXXX: Convert to skiplist or other better data structure 
 * (yes, this is VERY VERY VERY VERY BAD)
 */

/* Structures to reuse */
static APR_RING_HEAD(timer_free_ring_t, timer_event_t) timer_free_ring;
/* Active timers */
