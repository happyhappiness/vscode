{
    assert(stream->accepted_fd == -1);

#if defined(UV_HAVE_KQUEUE)
    if (w->rcount <= 0)
      return;
#endif /* defined(UV_HAVE_KQUEUE) */

    err = uv__accept(uv__stream_fd(stream));
    if (err < 0) {
      if (err == -EAGAIN || err == -EWOULDBLOCK)
        return;  /* Not an error. */

      if (err == -ECONNABORTED)
        continue;  /* Ignore. Nothing we can do about that. */

      if (err == -EMFILE || err == -ENFILE) {
        err = uv__emfile_trick(loop, uv__stream_fd(stream));
        if (err == -EAGAIN || err == -EWOULDBLOCK)
          break;
      }

      stream->connection_cb(stream, err);
      continue;
    }

    UV_DEC_BACKLOG(w)
    stream->accepted_fd = err;
    stream->connection_cb(stream, 0);

    if (stream->accepted_fd != -1) {
      /* The user hasn't yet accepted called uv_accept() */
      uv__io_stop(loop, &stream->io_watcher, POLLIN);
      return;
    }

    if (stream->type == UV_TCP && (stream->flags & UV_TCP_SINGLE_ACCEPT)) {
      /* Give other processes a chance to accept connections. */
      struct timespec timeout = { 0, 1 };
      nanosleep(&timeout, NULL);
    }
  }