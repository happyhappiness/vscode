static apr_status_t close_listeners_on_exec(void *v)
{
    ap_listen_rec *lr;

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_socket_close(lr->sd);
        lr->active = 0;
    }

    return APR_SUCCESS;
}