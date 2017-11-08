static int start_lingering_close_nonblocking(event_conn_state_t *cs)
{
    conn_rec *c = cs->c;
    apr_socket_t *csd = cs->pfd.desc.s;

    if (c->aborted
        || apr_socket_shutdown(csd, APR_SHUTDOWN_WRITE) != APR_SUCCESS) {
        apr_socket_close(csd);
        apr_pool_clear(cs->p);
        ap_push_pool(worker_queue_info, cs->p);
        return 0;
    }
    return start_lingering_close_common(cs);
}