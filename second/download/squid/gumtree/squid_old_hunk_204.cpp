
    /*
     * At this point the reply headers have been parsed and consumed.
     * That means header content has been removed from readBuf and
     * it contains only body data.
     */
    if (flags.chunked) {
        if (!decodeAndWriteReplyBody()) {
            flags.do_next_read = 0;
            serverComplete();
            return;
        }
    } else
        writeReplyBody();

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        /*
         * The above writeReplyBody() call could ABORT this entry,
         * in that case, the server FD should already be closed.
         * there's nothing for us to do.
         */
        (void) 0;
    } else
        switch (persistentConnStatus()) {
        case INCOMPLETE_MSG:
            debugs(11, 5, "processReplyBody: INCOMPLETE_MSG");
            /* Wait for more data or EOF condition */
            if (flags.keepalive_broken) {
                call = NULL;
                commSetTimeout(fd, 10, call);
            } else {
                call = NULL;
                commSetTimeout(fd, Config.Timeout.read, call);
            }

            flags.do_next_read = 1;
            break;

        case COMPLETE_PERSISTENT_MSG:
            debugs(11, 5, "processReplyBody: COMPLETE_PERSISTENT_MSG");
            /* yes we have to clear all these! */
            call = NULL;
            commSetTimeout(fd, -1, call);
            flags.do_next_read = 0;

            comm_remove_close_handler(fd, closeHandler);
            closeHandler = NULL;
            fwd->unregister(fd);

            if (orig_request->flags.spoof_client_ip)
                client_addr = orig_request->client_addr;


            if (request->flags.pinned) {
                ispinned = true;
            } else if (request->flags.connection_auth && request->flags.auth_sent) {
                ispinned = true;
            }

            if (orig_request->pinnedConnection() && ispinned) {
                orig_request->pinnedConnection()->pinConnection(fd, orig_request, _peer,
                        (request->flags.connection_auth != 0));
            } else {
                fwd->pconnPush(fd, _peer, request, orig_request->GetHost(), client_addr);
            }

            fd = -1;

            serverComplete();
            return;

        case COMPLETE_NONPERSISTENT_MSG:
            debugs(11, 5, "processReplyBody: COMPLETE_NONPERSISTENT_MSG");
            serverComplete();
            return;
        }

    maybeReadVirginBody();
}

void
HttpStateData::maybeReadVirginBody()
{
    // too late to read
    if (fd >= 0 && fd_table[fd].closing())
        return;

    // we may need to grow the buffer if headers do not fit
    const int minRead = flags.headers_parsed ? 0 :1024;
    const int read_size = replyBodySpace(*readBuf, minRead);

    debugs(11,9, HERE << (flags.do_next_read ? "may" : "wont") <<
           " read up to " << read_size << " bytes from FD " << fd);

    /*
     * why <2? Because delayAwareRead() won't actually read if
     * you ask it to read 1 byte.  The delayed read request
     * just gets re-queued until the client side drains, then
     * the I/O thread hangs.  Better to not register any read
