
    /*
     * At this point the reply headers have been parsed and consumed.
     * That means header content has been removed from readBuf and
     * it contains only body data.
     */
    if (entry->isAccepting()) {
        if (flags.chunked) {
            if (!decodeAndWriteReplyBody()) {
                flags.do_next_read = 0;
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

            flags.do_next_read = 1;
        }
        break;

        case COMPLETE_PERSISTENT_MSG:
            debugs(11, 5, "processReplyBody: COMPLETE_PERSISTENT_MSG from " << serverConnection);
            /* yes we have to clear all these! */
            commUnsetConnTimeout(serverConnection);
            flags.do_next_read = 0;

            comm_remove_close_handler(serverConnection->fd, closeHandler);
            closeHandler = NULL;
            fwd->unregister(serverConnection);

            if (request->flags.spoof_client_ip)
                client_addr = request->client_addr;


            if (request->flags.pinned) {
                ispinned = true;
            } else if (request->flags.connection_auth && request->flags.auth_sent) {
                ispinned = true;
            }

            if (ispinned && request->clientConnectionManager.valid()) {
                request->clientConnectionManager->pinConnection(serverConnection, request, _peer,
                        (request->flags.connection_auth != 0));
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

void
HttpStateData::maybeReadVirginBody()
{
    // too late to read
    if (!Comm::IsConnOpen(serverConnection) || fd_table[serverConnection->fd].closing())
        return;

    // we may need to grow the buffer if headers do not fit
    const int minRead = flags.headers_parsed ? 0 :1024;
    const int read_size = replyBodySpace(*readBuf, minRead);

    debugs(11,9, HERE << (flags.do_next_read ? "may" : "wont") <<
           " read up to " << read_size << " bytes from " << serverConnection);

    /*
     * why <2? Because delayAwareRead() won't actually read if
     * you ask it to read 1 byte.  The delayed read request
     * just gets re-queued until the client side drains, then
     * the I/O thread hangs.  Better to not register any read
