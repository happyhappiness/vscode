static apr_pollfd_t *find_poll_sock(apr_pollfd_t *aprset, apr_socket_t *sock)
{
    apr_pollfd_t *curr = aprset;
    
    while (curr->desc.s != sock) {
        if (curr->desc_type == APR_POLL_LASTDESC) {
            return NULL;
        }
        curr++;
    }

    return curr;
}