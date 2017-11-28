void
WhoisState::readReply(const Comm::ConnectionPointer &conn, char *aBuffer, size_t aBufferLength, comm_err_t flag, int xerrno)
{
    /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */
    if (flag == COMM_ERR_CLOSING)
        return;

    aBuffer[aBufferLength] = '\0';
    debugs(75, 3, HERE << conn << " read " << aBufferLength << " bytes");
    debugs(75, 5, "{" << aBuffer << "}");

    if (flag != COMM_OK) {
        debugs(50, 2, HERE  << conn << ": read failure: " << xstrerror() << ".");

        if (ignoreErrno(errno)) {
            AsyncCall::Pointer call = commCbCall(5,4, "whoisReadReply",
                                                 CommIoCbPtrFun(whoisReadReply, this));
            comm_read(conn, aBuffer, BUFSIZ, call);
        } else {
            ErrorState *err = new ErrorState(ERR_READ_ERROR, HTTP_INTERNAL_SERVER_ERROR, fwd->request);
            err->xerrno = xerrno;
            fwd->fail(err);
            conn->close();
        }
        return;
    }

    if (aBufferLength > 0) {
        if (!dataWritten)
            setReplyToOK(entry);

        kb_incr(&(statCounter.server.all.kbytes_in), aBufferLength);
        kb_incr(&(statCounter.server.http.kbytes_in), aBufferLength);

        /* No range support, we always grab it all */
        dataWritten = true;
        entry->append(aBuffer, aBufferLength);
        entry->flush();

        AsyncCall::Pointer call = commCbCall(5,4, "whoisReadReply",
                                             CommIoCbPtrFun(whoisReadReply, this));
        comm_read(conn, aBuffer, BUFSIZ, call);
        return;
    }

    /* no bytes read. stop reading */
    entry->timestampsSet();
    entry->flush();

    if (!EBIT_TEST(entry->flags, RELEASE_REQUEST))
        entry->setPublicKey();

    fwd->complete();
    debugs(75, 3, "whoisReadReply: Done: " << entry->url());
    conn->close();
}