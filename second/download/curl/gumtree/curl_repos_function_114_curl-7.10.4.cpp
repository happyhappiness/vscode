static int fillbuffer(struct connectdata *conn,
                      int bytes)
{
  int buffersize = bytes;
  int nread;

  if(conn->bits.upload_chunky) {
    /* if chunked Transfer-Encoding */
    buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
    conn->upload_fromhere += 10; /* 32bit hex + CRLF */
  }
  
  nread = conn->fread(conn->upload_fromhere, 1,
                      buffersize, conn->fread_in);
          
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
    if(nread>hexlen) {
      /* append CRLF to the data */
      memcpy(conn->upload_fromhere +
             nread, "\r\n", 2);
      nread+=2;
    }
    else {
      /* mark this as done once this chunk is transfered */
      conn->keep.upload_done = TRUE;
    }
  }
  return nread;
}