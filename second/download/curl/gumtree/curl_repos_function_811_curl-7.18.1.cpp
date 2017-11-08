CURLcode Curl_client_write(struct connectdata *conn,
                           int type,
                           char *ptr,
                           size_t len)
{
  struct SessionHandle *data = conn->data;
  size_t wrote;

  /* If reading is actually paused, we're forced to append this chunk of data
     to the already held data, but only if it is the same type as otherwise it
     can't work and it'll return error instead. */
  if(data->req.keepon & KEEP_READ_PAUSE) {
    size_t newlen;
    char *newptr;
    if(type != data->state.tempwritetype)
      /* major internal confusion */
      return CURLE_RECV_ERROR;

    /* figure out the new size of the data to save */
    newlen = len + data->state.tempwritesize;
    /* allocate the new memory area */
    newptr = malloc(newlen);
    if(!newptr)
      return CURLE_OUT_OF_MEMORY;
    /* copy the previously held data to the new area */
    memcpy(newptr, data->state.tempwrite, data->state.tempwritesize);
    /* copy the new data to the end of the new area */
    memcpy(newptr + data->state.tempwritesize, ptr, len);
    /* free the old data */
    free(data->state.tempwrite);
    /* update the pointer and the size */
    data->state.tempwrite = newptr;
    data->state.tempwritesize = newlen;

    return CURLE_OK;
  }

  if(0 == len)
    len = strlen(ptr);

  if(type & CLIENTWRITE_BODY) {
    if((conn->protocol&PROT_FTP) && conn->proto.ftpc.transfertype == 'A') {
#ifdef CURL_DOES_CONVERSIONS
      /* convert from the network encoding */
      size_t rc;
      rc = Curl_convert_from_network(data, ptr, len);
      /* Curl_convert_from_network calls failf if unsuccessful */
      if(rc != CURLE_OK)
        return rc;
#endif /* CURL_DOES_CONVERSIONS */

#ifdef CURL_DO_LINEEND_CONV
      /* convert end-of-line markers */
      len = convert_lineends(data, ptr, len);
#endif /* CURL_DO_LINEEND_CONV */
    }
    /* If the previous block of data ended with CR and this block of data is
       just a NL, then the length might be zero */
    if(len) {
      wrote = data->set.fwrite_func(ptr, 1, len, data->set.out);
    }
    else {
      wrote = len;
    }

    if(CURL_WRITEFUNC_PAUSE == wrote)
      return pausewrite(data, type, ptr, len);

    if(wrote != len) {
      failf(data, "Failed writing body (%d != %d)", (int)wrote, (int)len);
      return CURLE_WRITE_ERROR;
    }
  }

  if((type & CLIENTWRITE_HEADER) &&
     (data->set.fwrite_header || data->set.writeheader) ) {
    /*
     * Write headers to the same callback or to the especially setup
     * header callback function (added after version 7.7.1).
     */
    curl_write_callback writeit=
      data->set.fwrite_header?data->set.fwrite_header:data->set.fwrite_func;

    /* Note: The header is in the host encoding
       regardless of the ftp transfer mode (ASCII/Image) */

    wrote = writeit(ptr, 1, len, data->set.writeheader);
    if(CURL_WRITEFUNC_PAUSE == wrote)
      /* here we pass in the HEADER bit only since if this was body as well
         then it was passed already and clearly that didn't trigger the pause,
         so this is saved for later with the HEADER bit only */
      return pausewrite(data, CLIENTWRITE_HEADER, ptr, len);

    if(wrote != len) {
      failf (data, "Failed writing header");
      return CURLE_WRITE_ERROR;
    }
  }

  return CURLE_OK;
}