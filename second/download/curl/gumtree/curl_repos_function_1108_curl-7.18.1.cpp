CURLcode curl_easy_pause(CURL *curl, int action)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;
  struct SingleRequest *k = &data->req;
  CURLcode result = CURLE_OK;

  /* first switch off both pause bits */
  int newstate = k->keepon &~ (KEEP_READ_PAUSE| KEEP_WRITE_PAUSE);

  /* set the new desired pause bits */
  newstate |= ((action & CURLPAUSE_RECV)?KEEP_READ_PAUSE:0) |
    ((action & CURLPAUSE_SEND)?KEEP_WRITE_PAUSE:0);

  /* put it back in the keepon */
  k->keepon = newstate;

  if(!(newstate & KEEP_READ_PAUSE) && data->state.tempwrite) {
    /* we have a buffer for writing that we now seem to be able to deliver since
       the receive pausing is lifted! */

    /* get the pointer, type and length in local copies since the function may
       return PAUSE again and then we'll get a new copy allocted and stored in
       the tempwrite variables */
    char *tempwrite = data->state.tempwrite;
    size_t tempsize = data->state.tempwritesize;
    int temptype = data->state.tempwritetype;
    size_t chunklen;

    /* clear tempwrite here just to make sure it gets cleared if there's no
       further use of it, and make sure we don't clear it after the function
       invoke as it may have been set to a new value by then */
    data->state.tempwrite = NULL;

    /* since the write callback API is define to never exceed
       CURL_MAX_WRITE_SIZE bytes in a single call, and since we may in fact
       have more data than that in our buffer here, we must loop sending the
       data in multiple calls until there's no data left or we get another
       pause returned.

       A tricky part is that the function we call will "buffer" the data
       itself when it pauses on a particular buffer, so we may need to do some
       extra trickery if we get a pause return here.
    */
    do {
      chunklen = (tempsize > CURL_MAX_WRITE_SIZE)?CURL_MAX_WRITE_SIZE:tempsize;

      result = Curl_client_write(data->state.current_conn,
                                 temptype, tempwrite, chunklen);
      if(!result)
        /* failures abort the loop at once */
        break;

      if(data->state.tempwrite && (tempsize - chunklen)) {
        /* Ouch, the reading is again paused and the block we send is now
           "cached". If this is the final chunk we can leave it like this, but
           if we have more chunks that is cached after this, we need to free
           the newly cached one and put back a version that is truly the entire
           contents that is saved for later
        */
        char *newptr;

        free(data->state.tempwrite); /* free the one just cached as it isn't
                                        enough */

        /* note that tempsize is still the size as before the callback was
           used, and thus the whole piece of data to keep */
        newptr = malloc(tempsize);
        if(!newptr) {
          result = CURLE_OUT_OF_MEMORY;
          /* tempwrite will be freed further down */
          break;
        }
        data->state.tempwrite = newptr; /* store new pointer */
        memcpy(newptr, tempwrite, tempsize);
        data->state.tempwritesize = tempsize; /* store new size */
        /* tempwrite will be freed further down */
        break; /* go back to pausing until further notice */
      }
      else {
        tempsize -= chunklen;  /* left after the call above */
        tempwrite += chunklen; /* advance the pointer */
      }

    } while((result == CURLE_OK) && tempsize);

    free(tempwrite); /* this is unconditionally no longer used */
  }

  return result;
}