 * This permits the MPM to skip the poll when there is only one listening
 * socket, because it provides a alternate way to unblock an accept() when
 * the pod is used.
 */
static apr_status_t dummy_connection(ap_pod_t *pod)
{
    apr_status_t rv;
    apr_socket_t *sock;
    apr_pool_t *p;

    /* create a temporary pool for the socket.  pconf stays around too long */
    rv = apr_pool_create(&p, pod->p);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    rv = apr_socket_create(&sock, ap_listeners->bind_addr->family, SOCK_STREAM, p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, ap_server_conf,
                     "get socket to connect to listener");
        return rv;
    }

    /* on some platforms (e.g., FreeBSD), the kernel won't accept many
     * queued connections before it starts blocking local connects...
     * we need to keep from blocking too long and instead return an error,
