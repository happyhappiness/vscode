void
HttpStateData::processReplyBody()
{
    Ip::Address client_addr;
    bool ispinned = false;

    if (!flags.headers_parsed) {
        flags.do_next_read = true;
        maybeReadVirginBody();
        return;
    }

#if USE_ADAPTATION
    debugs(11,5, HERE << "adaptationAccessCheckPending=" << adaptationAccessCheckPending);
    if (adaptationAccessCheckPending)
        return;

#endif

    /*
     * At this point the reply headers have been parsed and consumed.
     * That means header content has been removed from readBuf and
     * it contains only body data.
     */
    if (entry->isAccepting()) {
        if (flags.chunked) {
            if (!decodeAndWriteReplyBody()) {
                flags.do_next_read = false;
                serverComplete();
                return;
            }
        } else
            writeReplyBody();
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        // The above writeReplyBody() call may have aborted the store entry.
        abortTransaction("store entry aborted while storing reply");
        return;
    } else
        switch (persistentConnStatus()) {
        case INCOMPLETE_MSG: {
            debugs(11, 5, "processReplyBody: INCOMPLETE_MSG from " << serverConnection);
            /* Wait for more data or EOF condition */
            AsyncCall::Pointer nil;
            if (flags.keepalive_broken) {
                commSetConnTimeout(serverConnection, 10, nil);
            } else {
                commSetConnTimeout(serverConnection, Config.Timeout.read, nil);
            }

            flags.do_next_read = true;
        }
        break;

        case COMPLETE_PERSISTENT_MSG:
            debugs(11, 5, "processReplyBody: COMPLETE_PERSISTENT_MSG from " << serverConnection);
            /* yes we have to clear all these! */
            commUnsetConnTimeout(serverConnection);
            flags.do_next_read = false;

            comm_remove_close_handler(serverConnection->fd, closeHandler);
            closeHandler = NULL;
            fwd->unregister(serverConnection);

            if (request->flags.spoofClientIp)
                client_addr = request->client_addr;

            if (request->flags.pinned) {
                ispinned = true;
            } else if (request->flags.connectionAuth && request->flags.authSent) {
                ispinned = true;
            }

            if (ispinned && request->clientConnectionManager.valid()) {
                request->clientConnectionManager->pinConnection(serverConnection, request, _peer,
                        (request->flags.connectionAuth != 0));
            } else {
                fwd->pconnPush(serverConnection, request->GetHost());
            }

            serverConnection = NULL;
            serverComplete();
            return;

        case COMPLETE_NONPERSISTENT_MSG:
            debugs(11, 5, "processReplyBody: COMPLETE_NONPERSISTENT_MSG from " << serverConnection);
            serverComplete();
            return;
        }

    maybeReadVirginBody();
}