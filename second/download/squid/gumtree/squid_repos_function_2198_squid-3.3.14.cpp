void
ServerStateData::sentRequestBody(const CommIoCbParams &io)
{
    debugs(11, 5, "sentRequestBody: FD " << io.fd << ": size " << io.size << ": errflag " << io.flag << ".");
    debugs(32,3,HERE << "sentRequestBody called");

    requestSender = NULL;

    if (io.size > 0) {
        fd_bytes(io.fd, io.size, FD_WRITE);
        kb_incr(&(statCounter.server.all.kbytes_out), io.size);
        // kids should increment their counters
    }

    if (io.flag == COMM_ERR_CLOSING)
        return;

    if (!requestBodySource) {
        debugs(9,3, HERE << "detected while-we-were-sending abort");
        return; // do nothing;
    }

    if (io.flag) {
        debugs(11, DBG_IMPORTANT, "sentRequestBody error: FD " << io.fd << ": " << xstrerr(io.xerrno));
        ErrorState *err;
        err = new ErrorState(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
        err->xerrno = io.xerrno;
        fwd->fail(err);
        abortTransaction("I/O error while sending request body");
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("store entry aborted while sending request body");
        return;
    }

    if (!requestBodySource->exhausted())
        sendMoreRequestBody();
    else if (receivedWholeRequestBody)
        doneSendingRequestBody();
    else
        debugs(9,3, HERE << "waiting for body production end or abort");
}