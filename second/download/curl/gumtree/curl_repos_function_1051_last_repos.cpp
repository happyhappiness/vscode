CURLcode Curl_fillreadbuffer(struct connectdata *conn, int bytes, int *nreadp)
{
  struct Curl_easy *data = conn->data;
  size_t buffersize = (size_t)bytes;
  int nread;
#ifdef CURL_DOES_CONVERSIONS
  bool sending_http_headers = FALSE;

  if(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)) {
    const struct HTTP *http = data->req.protop;

    if(http->sending == HTTPSEND_REQUEST)
      /* We're sending the HTTP request headers, not the data.
         Remember that so we don't re-translate them into garbage. */
      sending_http_headers = TRUE;
  }
#endif

  if(data->req.upload_chunky) {
    /* if chunked Transfer-Encoding */
    buffersize -= (8 + 2 + 2);   /* 32bit hex + CRLF + CRLF */
    data->req.upload_fromhere += (8 + 2); /* 32bit hex + CRLF */
  }

  /* this function returns a size_t, so we typecast to int to prevent warnings
     with picky compilers */
  nread = (int)data->state.fread_func(data->req.upload_fromhere, 1,
                                      buffersize, data->state.in);

  if(nread == CURL_READFUNC_ABORT) {
    failf(data, "operation aborted by callback");
    *nreadp = 0;
    return CURLE_ABORTED_BY_CALLBACK;
  }
  if(nread == CURL_READFUNC_PAUSE) {
    struct SingleRequest *k = &data->req;

    if(conn->handler->flags & PROTOPT_NONETWORK) {
      /* protocols that work without network cannot be paused. This is
         actually only FILE:// just now, and it can't pause since the transfer
         isn't done using the "normal" procedure. */
      failf(data, "Read callback asked for PAUSE when not supported!");
      return CURLE_READ_ERROR;
    }

    /* CURL_READFUNC_PAUSE pauses read callbacks that feed socket writes */
    k->keepon |= KEEP_SEND_PAUSE; /* mark socket send as paused */
    if(data->req.upload_chunky) {
        /* Back out the preallocation done above */
      data->req.upload_fromhere -= (8 + 2);
    }
    *nreadp = 0;

    return CURLE_OK; /* nothing was read */
  }
  else if((size_t)nread > buffersize) {
    /* the read function returned a too large value */
    *nreadp = 0;
    failf(data, "read function returned funny value");
    return CURLE_READ_ERROR;
  }

  if(!data->req.forbidchunk && data->req.upload_chunky) {
    /* if chunked Transfer-Encoding
     *    build chunk:
     *
     *        <HEX SIZE> CRLF
     *        <DATA> CRLF
     */
    /* On non-ASCII platforms the <DATA> may or may not be
       translated based on set.prefer_ascii while the protocol
       portion must always be translated to the network encoding.
       To further complicate matters, line end conversion might be
       done later on, so we need to prevent CRLFs from becoming
       CRCRLFs if that's the case.  To do this we use bare LFs
       here, knowing they'll become CRLFs later on.
     */

    char hexbuffer[11];
    const char *endofline_native;
    const char *endofline_network;
    int hexlen;

    if(
#ifdef CURL_DO_LINEEND_CONV
       (data->set.prefer_ascii) ||
#endif
       (data->set.crlf)) {
      /* \n will become \r\n later on */
      endofline_native  = "\n";
      endofline_network = "\x0a";
    }
    else {
      endofline_native  = "\r\n";
      endofline_network = "\x0d\x0a";
    }
    hexlen = snprintf(hexbuffer, sizeof(hexbuffer),
                      "%x%s", nread, endofline_native);

    /* move buffer pointer */
    data->req.upload_fromhere -= hexlen;
    nread += hexlen;

    /* copy the prefix to the buffer, leaving out the NUL */
    memcpy(data->req.upload_fromhere, hexbuffer, hexlen);

    /* always append ASCII CRLF to the data */
    memcpy(data->req.upload_fromhere + nread,
           endofline_network,
           strlen(endofline_network));

#ifdef CURL_DOES_CONVERSIONS
    {
      CURLcode result;
      int length;
      if(data->set.prefer_ascii)
        /* translate the protocol and data */
        length = nread;
      else
        /* just translate the protocol portion */
        length = (int)strlen(hexbuffer);
      result = Curl_convert_to_network(data, data->req.upload_fromhere,
                                       length);
      /* Curl_convert_to_network calls failf if unsuccessful */
      if(result)
        return result;
    }
#endif /* CURL_DOES_CONVERSIONS */

    if((nread - hexlen) == 0)
      /* mark this as done once this chunk is transferred */
      data->req.upload_done = TRUE;

    nread += (int)strlen(endofline_native); /* for the added end of line */
  }
#ifdef CURL_DOES_CONVERSIONS
  else if((data->set.prefer_ascii) && (!sending_http_headers)) {
    CURLcode result;
    result = Curl_convert_to_network(data, data->req.upload_fromhere, nread);
    /* Curl_convert_to_network calls failf if unsuccessful */
    if(result)
      return result;
  }
#endif /* CURL_DOES_CONVERSIONS */

  *nreadp = nread;

  return CURLE_OK;
}