void
HttpStateData::wroteLast(const CommIoCbParams &io)
{
    debugs(11, 5, HERE << serverConnection << ": size " << io.size << ": errflag " << io.flag << ".");
#if URL_CHECKSUM_DEBUG

    entry->mem_obj->checkUrlChecksum();
#endif

    if (io.size > 0) {
        fd_bytes(io.fd, io.size, FD_WRITE);
        statCounter.server.all.kbytes_out += io.size;
        statCounter.server.http.kbytes_out += io.size;
    }

    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (io.flag) {
        ErrorState *err = new ErrorState(ERR_WRITE_ERROR, Http::scBadGateway, fwd->request);
        err->xerrno = io.xerrno;
        fwd->fail(err);
        closeServer();
        mustStop("HttpStateData::wroteLast");
        return;
    }

    sendComplete();
}