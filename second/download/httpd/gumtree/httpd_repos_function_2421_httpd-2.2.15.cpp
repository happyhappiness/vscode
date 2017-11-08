static int shutdown_listeners()
{
    ap_listen_rec *lr;

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_socket_close(lr->sd);
    }
    ap_listeners = NULL;
    return 0;
}