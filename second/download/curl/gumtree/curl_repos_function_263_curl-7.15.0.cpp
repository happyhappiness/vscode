CURLcode Curl_fillreadbuffer(struct connectdata *conn, int bytes, int *nreadp)
{
  struct SessionHandle *data = conn->data;
  size_t buffersize = (size_t)bytes;
  int nread;

  if(conn->bits.upload_chunky) {
    /* if chunked Transfer-Encoding */
    buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
    conn->upload_fromhere += 10; /* 32bit hex + CRLF */
  }

  /* this function returns a size_t, so we typecast to int to prevent warnings
     with picky compilers */
  nread = (int)conn->fread(conn->upload_fromhere, 1,
                           buffersize, conn->fread_in);

  if(nread == CURL_READFUNC_ABORT) {
    failf(data, "operation aborted by callback\n");
    return CURLE_ABORTED_BY_CALLBACK;
  }

  if(!conn->bits.forbidchunk && conn->bits.upload_chunky) {
    /* if chunked Transfer-Encoding */
    char hexbuffer[11];
    int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
                          "%x\r\n", nread);
    /* move buffer pointer */
    conn->upload_fromhere -= hexlen;
    nread += hexlen;

    /* copy the prefix to the buffer */
    memcpy(conn->upload_fromhere, hexbuffer, hexlen);

    /* always append CRLF to the data */
    memcpy(conn->upload_fromhere + nread, "\r\n", 2);

    if((nread - hexlen) == 0) {
      /* mark this as done once this chunk is transfered */
      conn->keep.upload_done = TRUE;
    }

    nread+=2; /* for the added CRLF */
  }

  *nreadp = nread;

  return CURLE_OK;
}