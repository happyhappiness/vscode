static apr_status_t glassToWall(apr_int16_t port, apr_pool_t *parent)
{
    apr_sockaddr_t *sockAddr;
    apr_socket_t *listener, *accepted;
    apr_status_t rv;

    rv = apr_socket_create(&listener, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                           parent);
    if (rv != APR_SUCCESS) {
        reportError("Unable to create socket", rv, parent);
        return rv;
    }

    rv = apr_sockaddr_info_get(&sockAddr, "127.0.0.1", APR_UNSPEC,
                               port, 0, parent);
    if (rv != APR_SUCCESS) {
        reportError("Unable to get socket info", rv, parent);
        apr_socket_close(listener);
        return rv;
    }

    if ((rv = apr_socket_bind(listener, sockAddr)) != APR_SUCCESS ||
        (rv = apr_socket_listen(listener, 5)) != APR_SUCCESS) {
        reportError("Unable to bind or listen to socket", rv, parent);
        apr_socket_close(listener);
        return rv;
    }

    for (;;) {
        rv = apr_socket_accept(&accepted, listener, parent);
        if (rv != APR_SUCCESS) {
            reportError("Error accepting on socket", rv, parent);
            break;
        }
        printf("\tAnswering connection\n");
        rv = talkTalk(accepted, parent);
        apr_socket_close(accepted);
        printf("\tConnection closed\n");
        if (rv != APR_SUCCESS)
            break;
    }

    apr_socket_close(listener);
    return APR_SUCCESS;
}