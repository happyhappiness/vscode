{
    failf(data, "HTTP/2 stream %u was not closed cleanly: %s (err %d)",
          stream->stream_id, Curl_http2_strerror(stream->error_code),
          stream->error_code);
    *err = CURLE_HTTP2_STREAM;
    return -1;
  }