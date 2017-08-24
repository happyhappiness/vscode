{
  assert((stream->type == UV_TCP || stream->type == UV_NAMED_PIPE) &&
         "uv_shutdown (unix) only supports uv_handle_t right now");

  if (!(stream->flags & UV_STREAM_WRITABLE) ||
      stream->flags & UV_STREAM_SHUT ||
      stream->flags & UV_STREAM_SHUTTING ||
      uv__is_closing(stream)) {
    return -ENOTCONN;
  }

  assert(uv__stream_fd(stream) >= 0);

  /* Initialize request */
  uv__req_init(stream->loop, req, UV_SHUTDOWN);
  req->handle = stream;
  req->cb = cb;
  stream->shutdown_req = req;
  stream->flags |= UV_STREAM_SHUTTING;

  uv__io_start(stream->loop, &stream->io_watcher, POLLOUT);
  uv__stream_osx_interrupt_select(stream);

  return 0;
}