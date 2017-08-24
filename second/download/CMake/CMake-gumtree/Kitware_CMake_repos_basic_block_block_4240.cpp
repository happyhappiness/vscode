{
    /* If there is body data pending for this stream to return, do that */
    size_t left =
      stream->header_recvbuf->size_used - stream->nread_header_recvbuf;
    size_t ncopy = MIN(len, left);
    memcpy(mem, stream->header_recvbuf->buffer + stream->nread_header_recvbuf,
           ncopy);
    stream->nread_header_recvbuf += ncopy;

    DEBUGF(infof(data, "http2_recv: Got %d bytes from header_recvbuf\n",
                 (int)ncopy));
    return ncopy;
  }