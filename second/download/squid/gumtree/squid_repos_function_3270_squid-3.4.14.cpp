static void
gopherSendComplete(const Comm::ConnectionPointer &conn, char *buf, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    GopherStateData *gopherState = (GopherStateData *) data;
    StoreEntry *entry = gopherState->entry;
    debugs(10, 5, HERE << conn << " size: " << size << " errflag: " << errflag);

    if (size > 0) {
        fd_bytes(conn->fd, size, FD_WRITE);
        kb_incr(&(statCounter.server.all.kbytes_out), size);
        kb_incr(&(statCounter.server.other.kbytes_out), size);
    }

    if (errflag) {
        ErrorState *err;
        err = new ErrorState(ERR_WRITE_ERROR, Http::scServiceUnavailable, gopherState->fwd->request);
        err->xerrno = xerrno;
        err->port = gopherState->fwd->request->port;
        err->url = xstrdup(entry->url());
        gopherState->fwd->fail(err);
        gopherState->serverConn->close();

        if (buf)
            memFree(buf, MEM_4K_BUF);	/* Allocated by gopherSendRequest. */

        return;
    }

    /*
     * OK. We successfully reach remote site.  Start MIME typing
     * stuff.  Do it anyway even though request is not HTML type.
     */
    entry->buffer();

    gopherMimeCreate(gopherState);

    switch (gopherState->type_id) {

    case GOPHER_DIRECTORY:
        /* we got to convert it first */
        gopherState->conversion = gopher_ds::HTML_DIR;
        gopherState->HTML_header_added = 0;
        break;

    case GOPHER_INDEX:
        /* we got to convert it first */
        gopherState->conversion = gopher_ds::HTML_INDEX_RESULT;
        gopherState->HTML_header_added = 0;
        break;

    case GOPHER_CSO:
        /* we got to convert it first */
        gopherState->conversion = gopher_ds::HTML_CSO_RESULT;
        gopherState->cso_recno = 0;
        gopherState->HTML_header_added = 0;
        break;

    default:
        gopherState->conversion = gopher_ds::NORMAL;
        entry->flush();
    }

    /* Schedule read reply. */
    AsyncCall::Pointer call =  commCbCall(5,5, "gopherReadReply",
                                          CommIoCbPtrFun(gopherReadReply, gopherState));
    entry->delayAwareRead(conn, gopherState->replybuf, BUFSIZ, call);

    if (buf)
        memFree(buf, MEM_4K_BUF);	/* Allocated by gopherSendRequest. */
}