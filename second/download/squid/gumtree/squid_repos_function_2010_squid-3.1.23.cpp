void
HttpStateData::sendComplete(const CommIoCbParams &io)
{
    debugs(11, 5, "httpSendComplete: FD " << fd << ": size " << io.size << ": errflag " << io.flag << ".");
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    if (io.size > 0) {
        fd_bytes(fd, io.size, FD_WRITE);
        kb_incr(&statCounter.server.all.kbytes_out, io.size);
        kb_incr(&statCounter.server.http.kbytes_out, io.size);
    }

    if (io.flag == COMM_ERR_CLOSING)
        return;

    if (io.flag) {
        ErrorState *err;
        err = errorCon(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
        err->xerrno = io.xerrno;
        fwd->fail(err);
        comm_close(fd);
        return;
    }

    /*
     * Set the read timeout here because it hasn't been set yet.
     * We only set the read timeout after the request has been
     * fully written to the server-side.  If we start the timeout
     * after connection establishment, then we are likely to hit
     * the timeout for POST/PUT requests that have very large
     * request bodies.
     */
    typedef CommCbMemFunT<HttpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(11, 5,
                                      TimeoutDialer, this, HttpStateData::httpTimeout);

    commSetTimeout(fd, Config.Timeout.read, timeoutCall);

    flags.request_sent = 1;

    orig_request->hier.peer_http_request_sent = current_time;
}