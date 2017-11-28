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

void
httpStart(FwdState *fwd)
{
    debugs(11, 3, "httpStart: \"" << RequestMethodStr(fwd->request->method) << " " << fwd->entry->url() << "\"" );
    HttpStateData *httpState = new HttpStateData(fwd);

    if (!httpState->sendRequest()) {
        debugs(11, 3, "httpStart: aborted");
        delete httpState;
        return;
    }

    statCounter.server.all.requests++;
    statCounter.server.http.requests++;

    /*
     * We used to set the read timeout here, but not any more.
     * Now its set in httpSendComplete() after the full request,
     * including request body, has been written to the server.
     */
}

void
HttpStateData::doneSendingRequestBody()
{
    debugs(11,5, HERE << "doneSendingRequestBody: FD " << fd);

#if HTTP_VIOLATIONS
    if (Config.accessList.brokenPosts) {
        ACLFilledChecklist ch(Config.accessList.brokenPosts, originalRequest(), NULL);
        if (!ch.fastCheck()) {
            debugs(11, 5, "doneSendingRequestBody: didn't match brokenPosts");
            CommIoCbParams io(NULL);
            io.fd=fd;
            io.flag=COMM_OK;
            sendComplete(io);
        } else {
            debugs(11, 2, "doneSendingRequestBody: matched brokenPosts");

            if (!canSend(fd)) {
                debugs(11,2, HERE << "cannot send CRLF to closing FD " << fd);
                assert(closeHandler != NULL);
                return;
            }

            typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
            AsyncCall::Pointer call = JobCallback(11,5,
                                                  Dialer, this, HttpStateData::sendComplete);
            comm_write(fd, "\r\n", 2, call);
        }
        return;
    }
    debugs(11, 5, "doneSendingRequestBody: No brokenPosts list");
#endif /* HTTP_VIOLATIONS */

    CommIoCbParams io(NULL);
    io.fd=fd;
    io.flag=COMM_OK;
    sendComplete(io);
}

// more origin request body data is available
void
HttpStateData::handleMoreRequestBodyAvailable()
{
    if (eof || fd < 0) {
        // XXX: we should check this condition in other callbacks then!
        // TODO: Check whether this can actually happen: We should unsubscribe
        // as a body consumer when the above condition(s) are detected.
        debugs(11, 1, HERE << "Transaction aborted while reading HTTP body");
        return;
    }
