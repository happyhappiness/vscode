        }
    }

    return num_listeners;
}

AP_DECLARE_NONSTD(void) ap_close_listeners(void)
{
    ap_listen_rec *lr;

    for (lr = ap_listeners; lr; lr = lr->next) {
        apr_socket_close(lr->sd);
        lr->active = 0;
    }
}
AP_DECLARE_NONSTD(int) ap_close_selected_listeners(ap_slave_t *slave)
{
    ap_listen_rec *lr;
    int n = 0;

    for (lr = ap_listeners; lr; lr = lr->next) {
