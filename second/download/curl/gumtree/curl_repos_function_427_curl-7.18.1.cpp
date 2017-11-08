CURLcode Curl_fillreadbuffer(struct connectdata *conn, int bytes, int *nreadp)
{
  struct SessionHandle *data = conn->data;
  size_t buffersize = (size_t)bytes;
  int nread;

  if(data->req.upload_chunky) {
    /* if chunked Transfer-Encoding */
    buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
    data->req.upload_fromhere += 10; /* 32bit hex + CRLF */
  }

  /* this function returns a size_t, so we typecast to int to prevent warnings
     with picky compilers */
  nread = (int)conn->fread_func(data->req.upload_fromhere, 1,
                                buffersize, conn->fread_in);

  if(nread == CURL_READFUNC_ABORT) {
    failf(data, "operation aborted by callback");
    return CURLE_ABORTED_BY_CALLBACK;
  }
  else if(nread == CURL_READFUNC_PAUSE) {
    struct SingleRequest *k = &data->req;
    k->keepon |= KEEP_READ_PAUSE; /* mark reading as paused */
    return CURLE_OK; /* nothing was read */
  }
  else if((size_t)nread > buffersize)
    /* the read function returned a too large value */
    return CURLE_READ_ERROR;

  if(!data->req.forbidchunk && data->req.upload_chunky) {
    /* if chunked Transfer-Encoding */
    char hexbuffer[11];
    int hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
                          "%x\r\n", nread);
    /* move buffer pointer */
    data->req.upload_fromhere -= hexlen;
    nread += hexlen;

    /* copy the prefix to the buffer */
    memcpy(data->req.upload_fromhere, hexbuffer, hexlen);

    /* always append CRLF to the data */
    memcpy(data->req.upload_fromhere + nread, "\r\n", 2);

    if((nread - hexlen) == 0) {
      /* mark this as done once this chunk is transfered */
      data->req.upload_done = TRUE;
    }

    nread+=2; /* for the added CRLF */
  }

  *nreadp = nread;

#ifdef CURL_DOES_CONVERSIONS
  if(data->set.prefer_ascii) {
    CURLcode res;
    res = Curl_convert_to_network(data, data->req.upload_fromhere, nread);
    /* Curl_convert_to_network calls failf if unsuccessful */
    if(res != CURLE_OK) {
      return(res);
    }
  }
#endif /* CURL_DOES_CONVERSIONS */

  return CURLE_OK;
}