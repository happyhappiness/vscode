void
ConnStateData::requestTimeout(const CommTimeoutCbParams &io)
{
#if THIS_CONFUSES_PERSISTENT_CONNECTION_AWARE_BROWSERS_AND_USERS
    debugs(33, 3, "requestTimeout: FD " << io.fd << ": lifetime is expired.");

    if (COMMIO_FD_WRITECB(io.fd)->active) {
        /* FIXME: If this code is reinstated, check the conn counters,
         * not the fd table state
         */
        /*
         * Some data has been sent to the client, just close the FD
         */
        comm_close(io.fd);
    } else if (nrequests) {
        /*
         * assume its a persistent connection; just close it
         */
        comm_close(io.fd);
    } else {
        /*
         * Generate an error
         */
        ClientHttpRequest **H;
        clientStreamNode *node;
        ClientHttpRequest *http =
            parseHttpRequestAbort(this, "error:Connection%20lifetime%20expired");
        node = http->client_stream.tail->prev->data;
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        repContext->setReplyToError(ERR_LIFETIME_EXP,
                                    HTTP_REQUEST_TIMEOUT, METHOD_NONE, "N/A", &peer.sin_addr,
                                    NULL, NULL, NULL);
        /* No requests can be outstanded */
        assert(chr == NULL);
        /* add to the client request queue */

        for (H = &chr; *H; H = &(*H)->next);
        *H = http;

        clientStreamRead(http->client_stream.tail->data, http, 0,
                         HTTP_REQBUF_SZ, context->reqbuf);

        /*
         * if we don't close() here, we still need a timeout handler!
         */
        typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                          TimeoutDialer, this, ConnStateData::requestTimeout);
        commSetTimeout(io.fd, 30, timeoutCall);

        /*
         * Aha, but we don't want a read handler!
         */
        commSetSelect(io.fd, COMM_SELECT_READ, NULL, NULL, 0);
    }

#else
    /*
    * Just close the connection to not confuse browsers
    * using persistent connections. Some browsers opens
    * an connection and then does not use it until much
    * later (presumeably because the request triggering
    * the open has already been completed on another
    * connection)
    */
    debugs(33, 3, "requestTimeout: FD " << io.fd << ": lifetime is expired.");

    comm_close(io.fd);

#endif
}