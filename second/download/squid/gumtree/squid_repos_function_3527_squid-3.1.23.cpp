int ConnStateData::validatePinnedConnection(HttpRequest *request, const struct peer *aPeer)
{
    bool valid = true;
    if (pinning.fd < 0)
        return -1;

    if (pinning.auth && request && strcasecmp(pinning.host, request->GetHost()) != 0) {
        valid = false;
    }
    if (request && pinning.port != request->port) {
        valid = false;
    }
    if (pinning.peer && !cbdataReferenceValid(pinning.peer)) {
        valid = false;
    }
    if (aPeer != pinning.peer) {
        valid = false;
    }

    if (!valid) {
        int pinning_fd=pinning.fd;
        /* The pinning info is not safe, remove any pinning info*/
        unpinConnection();

        /* also close the server side socket, we should not use it for invalid/unauthenticated
           requests...
         */
        comm_close(pinning_fd);
        return -1;
    }

    return pinning.fd;
}