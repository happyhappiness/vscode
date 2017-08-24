{
    /* nghttp2 guarantees :status is received first and only once, and
       value is 3 digits status code, and decode_status_code always
       succeeds. */
    stream->status_code = decode_status_code(value, valuelen);
    DEBUGASSERT(stream->status_code != -1);

    Curl_add_buffer(stream->header_recvbuf, "HTTP/2 ", 7);
    Curl_add_buffer(stream->header_recvbuf, value, valuelen);
    /* the space character after the status code is mandatory */
    Curl_add_buffer(stream->header_recvbuf, " \r\n", 3);
    /* if we receive data for another handle, wake that up */
    if(conn->data != data_s)
      Curl_expire(data_s, 0, EXPIRE_RUN_NOW);

    DEBUGF(infof(data_s, "h2 status: HTTP/2 %03d (easy %p)\n",
                 stream->status_code, data_s));
    return 0;
  }