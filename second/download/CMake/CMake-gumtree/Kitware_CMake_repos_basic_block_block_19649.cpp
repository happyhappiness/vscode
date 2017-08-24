((events & POLLHUP) &&
      (stream->flags & UV_STREAM_READING) &&
      (stream->flags & UV_STREAM_READ_PARTIAL) &&
      !(stream->flags & UV_STREAM_READ_EOF)) {
    uv_buf_t buf = { NULL, 0 };
    uv__stream_eof(stream, &buf);
  }