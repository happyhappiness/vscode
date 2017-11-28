bool
HttpStateData::sendRequest()
{
    MemBuf mb;

    debugs(11, 5, "httpSendRequest: FD " << fd << ", request " << request << ", this " << this << ".");

    if (!canSend(fd)) {
        debugs(11,3, HERE << "cannot send request to closing FD " << fd);
        assert(closeHandler != NULL);
        return false;
    }

    typedef CommCbMemFunT<HttpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(11, 5,
                                      TimeoutDialer, this, HttpStateData::httpTimeout);
    commSetTimeout(fd, Config.Timeout.lifetime, timeoutCall);
    flags.do_next_read = 1;
    maybeReadVirginBody();

    if (orig_request->body_pipe != NULL) {
        if (!startRequestBodyFlow()) // register to receive body data
            return false;
        typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
        requestSender = JobCallback(11,5,
                                    Dialer, this, HttpStateData::sentRequestBody);
    } else {
        assert(!requestBodySource);
        typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
        requestSender = JobCallback(11,5,
                                    Dialer, this,  HttpStateData::sendComplete);
    }

    if (_peer != NULL) {
        if (_peer->options.originserver) {
            flags.proxying = 0;
            flags.originpeer = 1;
        } else {
            flags.proxying = 1;
            flags.originpeer = 0;
        }
    } else {
        flags.proxying = 0;
        flags.originpeer = 0;
    }

    /*
     * Is keep-alive okay for all request methods?
     */
    if (orig_request->flags.must_keepalive)
        flags.keepalive = 1;
    else if (!Config.onoff.server_pconns)
        flags.keepalive = 0;
    else if (_peer == NULL)
        flags.keepalive = 1;
    else if (_peer->stats.n_keepalives_sent < 10)
        flags.keepalive = 1;
    else if ((double) _peer->stats.n_keepalives_recv /
             (double) _peer->stats.n_keepalives_sent > 0.50)
        flags.keepalive = 1;

    if (_peer) {
        if (neighborType(_peer, request) == PEER_SIBLING &&
                !_peer->options.allow_miss)
            flags.only_if_cached = 1;

        flags.front_end_https = _peer->front_end_https;
    }

    mb.init();
    buildRequestPrefix(request, orig_request, entry, &mb);
    debugs(11, 6, "httpSendRequest: FD " << fd << ":\n" << mb.buf);
    comm_write_mbuf(fd, &mb, requestSender);

    return true;
}