{
    uv__stream_flush_write_queue(stream, -ECANCELED);
    uv__write_callbacks(stream);
  }