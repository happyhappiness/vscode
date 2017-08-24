{
    /* The ECANCELED error code is a lie, the shutdown(2) syscall is a
     * fait accompli at this point. Maybe we should revisit this in v0.11.
     * A possible reason for leaving it unchanged is that it informs the
     * callee that the handle has been destroyed.
     */
    uv__req_unregister(stream->loop, stream->shutdown_req);
    stream->shutdown_req->cb(stream->shutdown_req, -ECANCELED);
    stream->shutdown_req = NULL;
  }