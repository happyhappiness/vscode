void
Comm::IoCallback::finish(Comm::Flag code, int xerrn)
{
    debugs(5, 3, "called for " << conn << " (" << code << ", " << xerrn << ")");
    assert(active());

    /* free data */
    if (freefunc && buf) {
        freefunc(buf);
        buf = NULL;
        freefunc = NULL;
    }

    if (callback != NULL) {
        typedef CommIoCbParams Params;
        Params &params = GetCommParams<Params>(callback);
        if (conn != NULL) params.fd = conn->fd; // for legacy write handlers...
        params.conn = conn;
        params.buf = buf;
        params.size = offset;
        params.flag = code;
        params.xerrno = xerrn;
        ScheduleCallHere(callback);
        callback = NULL;
    }

    /* Reset for next round. */
    reset();
}