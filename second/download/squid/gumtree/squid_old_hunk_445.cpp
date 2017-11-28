    if (!requestBodySource) {
        debugs(9,3, HERE << "detected while-we-were-sending abort");
        return; // do nothing;
    }

    if (io.flag) {
        debugs(11, 1, "sentRequestBody error: FD " << io.fd << ": " << xstrerr(io.xerrno));
        ErrorState *err;
        err = new ErrorState(ERR_WRITE_ERROR, HTTP_BAD_GATEWAY, fwd->request);
        err->xerrno = io.xerrno;
        fwd->fail(err);
        abortTransaction("I/O error while sending request body");
        return;
