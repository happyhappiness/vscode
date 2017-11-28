void
WhoisState::readReply (int fd, char *aBuffer, size_t aBufferLength, comm_err_t flag, int xerrno)
{
    /* Bail out early on COMM_ERR_CLOSING - close handlers will tidy up for us */
    if (flag == COMM_ERR_CLOSING)
        return;

    aBuffer[aBufferLength] = '\0';
    debugs(75, 3, "whoisReadReply: FD " << fd << " read " << aBufferLength << " bytes");
    debugs(75, 5, "{" << aBuffer << "}");

    if (flag != COMM_OK) {
        debugs(50, 2, "whoisReadReply: FD " << fd << ": read failure: " << xstrerror() << ".");

        if (ignoreErrno(errno)) {
            comm_read(fd, aBuffer, BUFSIZ, whoisReadReply, this);
        } else {
            ErrorState *err;
            err = errorCon(ERR_READ_ERROR, HTTP_INTERNAL_SERVER_ERROR, fwd->request);
            err->xerrno = errno;
            fwd->fail(err);
            comm_close(fd);
        }
        return;
    }

    if (aBufferLength > 0) {
        if (!dataWritten)
            setReplyToOK(entry);

        kb_incr(&statCounter.server.all.kbytes_in, aBufferLength);
        kb_incr(&statCounter.server.http.kbytes_in, aBufferLength);

        /* No range support, we always grab it all */
        dataWritten = true;
        entry->append(aBuffer, aBufferLength);
        entry->flush();

        comm_read(fd, aBuffer, BUFSIZ, whoisReadReply, this);
        return;
    }

    /* no bytes read. stop reading */
    entry->timestampsSet();
    entry->flush();

    if (!EBIT_TEST(entry->flags, RELEASE_REQUEST))
        entry->setPublicKey();

    fwd->complete();
    debugs(75, 3, "whoisReadReply: Done: " << entry->url());
    comm_close(fd);
}