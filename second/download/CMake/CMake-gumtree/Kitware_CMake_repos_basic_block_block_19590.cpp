{
    assert(stream->shutdown_req);

    req = stream->shutdown_req;
    stream->shutdown_req = NULL;
    stream->flags &= ~UV_STREAM_SHUTTING;
    uv__req_unregister(stream->loop, req);

    err = 0;
    if (shutdown(uv__stream_fd(stream), SHUT_WR))
      err = -errno;

    if (err == 0)
      stream->flags |= UV_STREAM_SHUT;

    if (req->cb != NULL)
      req->cb(req, err);
  }