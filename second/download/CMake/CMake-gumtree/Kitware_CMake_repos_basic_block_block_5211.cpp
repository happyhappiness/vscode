{
    if(length < (size_t)len)
      len = length;

    do_sec_send(conn, fd, buffer, curlx_sztosi(len));
    length -= len;
    buffer += len;
    tx += len;
  }