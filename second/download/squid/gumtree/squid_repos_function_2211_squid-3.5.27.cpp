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
     * handler until we get a notification from someone that
     * its okay to read again.
     */
    if (read_size < 2)
        return;

    if (flags.do_next_read) {
        flags.do_next_read = false;
        typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
        entry->delayAwareRead(serverConnection, readBuf->space(read_size), read_size,
                              JobCallback(11, 5, Dialer, this,  HttpStateData::readReply));
    }
}