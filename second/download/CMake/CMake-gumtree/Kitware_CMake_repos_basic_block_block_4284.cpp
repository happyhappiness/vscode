f(stream->closed) {
      return http2_handle_stream_close(conn, conn->data, stream, err);
    }