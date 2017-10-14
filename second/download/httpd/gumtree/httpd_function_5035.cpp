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