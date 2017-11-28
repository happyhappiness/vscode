void ConnStateData::pinConnection(int pinning_fd, HttpRequest *request, struct peer *aPeer, bool auth)
{
    fde *f;
    char desc[FD_DESC_SZ];

    if (pinning.fd == pinning_fd)
        return;
    else if (pinning.fd != -1)
        comm_close(pinning.fd);

    if (pinning.host)
        safe_free(pinning.host);

    pinning.fd = pinning_fd;
    pinning.host = xstrdup(request->GetHost());
    pinning.port = request->port;
    pinning.pinned = true;
    if (pinning.peer)
        cbdataReferenceDone(pinning.peer);
    if (aPeer)
        pinning.peer = cbdataReference(aPeer);
    pinning.auth = auth;
    f = &fd_table[fd];
    snprintf(desc, FD_DESC_SZ, "%s pinned connection for %s:%d (%d)",
             (auth || !aPeer) ? request->GetHost() : aPeer->name, f->ipaddr, (int) f->remote_port, fd);
    fd_note(pinning_fd, desc);

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    pinning.closeHandler = JobCallback(33, 5,
                                       Dialer, this, ConnStateData::clientPinnedConnectionClosed);
    comm_add_close_handler(pinning_fd, pinning.closeHandler);

}