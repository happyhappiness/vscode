{
    failf(data, "HTTP/2 stream %u was closed cleanly, but before getting "
          " all response header fields, teated as error",
          stream->stream_id);
    *err = CURLE_HTTP2_STREAM;
    return -1;
  }