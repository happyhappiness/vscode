f(stream->closed) {
    return http2_handle_stream_close(conn, data, stream, err);
  }