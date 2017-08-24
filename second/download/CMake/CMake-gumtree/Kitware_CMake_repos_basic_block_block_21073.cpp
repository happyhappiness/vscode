{
    read_bytes = WideCharToMultiByte(CP_UTF8,
                                     0,
                                     utf16,
                                     read_chars,
                                     handle->tty.rd.read_line_buffer.base,
                                     bytes,
                                     NULL,
                                     NULL);
    SET_REQ_SUCCESS(req);
    req->u.io.overlapped.InternalHigh = read_bytes;
  }