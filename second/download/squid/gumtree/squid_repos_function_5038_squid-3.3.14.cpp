void
Comm::IoCallback::finish(comm_err_t code, int xerrn)
{
    debugs(5, 3, HERE << "called for " << conn << " (" << code << ", " << xerrno << ")");
    assert(active());

    /* free data */
    if (freefunc) {
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