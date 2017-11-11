CURLcode Curl_read(struct connectdata *conn, /* connection data */
                   curl_socket_t sockfd,     /* read from this socket */
                   char *buf,                /* store read data here */
                   size_t sizerequested,     /* max amount to read */
                   ssize_t *n)               /* amount bytes read */
{
  CURLcode curlcode = CURLE_RECV_ERROR;
  ssize_t nread = 0;
  size_t bytesfromsocket = 0;
  char *buffertofill = NULL;
  bool pipelining = Curl_multi_pipeline_enabled(conn->data->multi);

  /* Set 'num' to 0 or 1, depending on which socket that has been sent here.
     If it is the second socket, we set num to 1. Otherwise to 0. This lets
     us use the correct ssl handle. */
  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  *n=0; /* reset amount to zero */

  /* If session can pipeline, check connection buffer  */
  if(pipelining) {
    size_t bytestocopy = CURLMIN(conn->buf_len - conn->read_pos,
                                 sizerequested);

    /* Copy from our master buffer first if we have some unread data there*/
    if(bytestocopy > 0) {
      memcpy(buf, conn->master_buffer + conn->read_pos, bytestocopy);
      conn->read_pos += bytestocopy;
      conn->bits.stream_was_rewound = FALSE;

      *n = (ssize_t)bytestocopy;
      return CURLE_OK;
    }
    /* If we come here, it means that there is no data to read from the buffer,
     * so we read from the socket */
    bytesfromsocket = CURLMIN(sizerequested, BUFSIZE * sizeof (char));
    buffertofill = conn->master_buffer;
  }
  else {
    bytesfromsocket = CURLMIN((long)sizerequested,
                              conn->data->set.buffer_size ?
                              conn->data->set.buffer_size : BUFSIZE);
    buffertofill = buf;
  }

  nread = conn->recv[num](conn, num, buffertofill, bytesfromsocket, &curlcode);
  if(nread < 0)
    return curlcode;

  if(pipelining) {
    memcpy(buf, conn->master_buffer, nread);
    conn->buf_len = nread;
    conn->read_pos = nread;
  }

  *n += nread;

  return CURLE_OK;
}