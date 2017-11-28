        return; // do nothing;
    }

    if (io.flag) {
        debugs(11, DBG_IMPORTANT, "sentRequestBody error: FD " << io.fd << ": " << xstrerr(io.xerrno));
        ErrorState *err;
        err = new ErrorState(ERR_WRITE_ERROR, Http::scBadGateway, fwd->request);
        err->xerrno = io.xerrno;
        fwd->fail(err);
        abortTransaction("I/O error while sending request body");
        return;
    }

