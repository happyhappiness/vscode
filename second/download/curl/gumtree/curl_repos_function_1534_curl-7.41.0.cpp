CURLcode Curl_client_chop_write(struct connectdata *conn,
                                int type,
                                char * ptr,
                                size_t len)
{
  struct SessionHandle *data = conn->data;
  curl_write_callback writeheader = NULL;
  curl_write_callback writebody = NULL;

  if(!len)
    return CURLE_OK;

  /* If reading is actually paused, we're forced to append this chunk of data
     to the already held data, but only if it is the same type as otherwise it
     can't work and it'll return error instead. */
  if(data->req.keepon & KEEP_RECV_PAUSE) {
    size_t newlen;
    char *newptr;
    if(type != data->state.tempwritetype)
      /* major internal confusion */
      return CURLE_RECV_ERROR;

    DEBUGASSERT(data->state.tempwrite);

    /* figure out the new size of the data to save */
    newlen = len + data->state.tempwritesize;
    /* allocate the new memory area */
    newptr = realloc(data->state.tempwrite, newlen);
    if(!newptr)
      return CURLE_OUT_OF_MEMORY;
    /* copy the new data to the end of the new area */
    memcpy(newptr + data->state.tempwritesize, ptr, len);
    /* update the pointer and the size */
    data->state.tempwrite = newptr;
    data->state.tempwritesize = newlen;
    return CURLE_OK;
  }

  /* Determine the callback(s) to use. */
  if(type & CLIENTWRITE_BODY)
    writebody = data->set.fwrite_func;
  if((type & CLIENTWRITE_HEADER) &&
     (data->set.fwrite_header || data->set.writeheader)) {
    /*
     * Write headers to the same callback or to the especially setup
     * header callback function (added after version 7.7.1).
     */
    writeheader =
      data->set.fwrite_header? data->set.fwrite_header: data->set.fwrite_func;
  }

  /* Chop data, write chunks. */
  while(len) {
    size_t chunklen = len <= CURL_MAX_WRITE_SIZE? len: CURL_MAX_WRITE_SIZE;

    if(writebody) {
      size_t wrote = writebody(ptr, 1, chunklen, data->set.out);

      if(CURL_WRITEFUNC_PAUSE == wrote) {
        if(conn->handler->flags & PROTOPT_NONETWORK) {
          /* Protocols that work without network cannot be paused. This is
             actually only FILE:// just now, and it can't pause since the
             transfer isn't done using the "normal" procedure. */
          failf(data, "Write callback asked for PAUSE when not supported!");
          return CURLE_WRITE_ERROR;
        }
        else
          return pausewrite(data, type, ptr, len);
      }
      else if(wrote != chunklen) {
        failf(data, "Failed writing body (%zu != %zu)", wrote, chunklen);
        return CURLE_WRITE_ERROR;
      }
    }

    if(writeheader) {
      size_t wrote = writeheader(ptr, 1, chunklen, data->set.writeheader);

      if(CURL_WRITEFUNC_PAUSE == wrote)
        /* here we pass in the HEADER bit only since if this was body as well
           then it was passed already and clearly that didn't trigger the
           pause, so this is saved for later with the HEADER bit only */
        return pausewrite(data, CLIENTWRITE_HEADER, ptr, len);

      if(wrote != chunklen) {
        failf (data, "Failed writing header");
        return CURLE_WRITE_ERROR;
      }
    }

    ptr += chunklen;
    len -= chunklen;
  }

  return CURLE_OK;
}