static apr_status_t nwssl_socket_cleanup(void *data)
{
    ap_listen_rec* slr = (ap_listen_rec*)data;
    ap_listen_rec* lr;

    /* Remove our secure listener from the listener list */
    for (lr = ap_listeners; lr; lr = lr->next) {
        /* slr is at the head of the list */
        if (lr == slr) {
            ap_listeners = slr->next;
            break;
        }
        /* slr is somewhere in between or at the end*/
        if (lr->next == slr) {
            lr->next = slr->next;
            break;
        }
    }
    return APR_SUCCESS;
}