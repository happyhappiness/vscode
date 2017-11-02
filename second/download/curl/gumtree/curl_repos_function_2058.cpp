CURLcode curl_easy_pause(CURL *curl, int action)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;
  struct SingleRequest *k = &data->req;
  CURLcode result = CURLE_OK;

  /* first switch off both pause bits */
  int newstate = k->keepon &~ (KEEP_RECV_PAUSE| KEEP_SEND_PAUSE);

  /* set the new desired pause bits */
  newstate |= ((action & CURLPAUSE_RECV)?KEEP_RECV_PAUSE:0) |
    ((action & CURLPAUSE_SEND)?KEEP_SEND_PAUSE:0);

  /* put it back in the keepon */
  k->keepon = newstate;

  if(!(newstate & KEEP_RECV_PAUSE) && data->state.tempwrite) {
    /* we have a buffer for sending that we now seem to be able to deliver
       since the receive pausing is lifted! */

    /* get the pointer in local copy since the function may return PAUSE
       again and then we'll get a new copy allocted and stored in
       the tempwrite variables */
    char *tempwrite = data->state.tempwrite;

    data->state.tempwrite = NULL;
    result = Curl_client_chop_write(data->easy_conn, data->state.tempwritetype,
                                    tempwrite, data->state.tempwritesize);
    free(tempwrite);
  }

  /* if there's no error and we're not pausing both directions, we want
     to have this handle checked soon */
  if(!result &&
     ((newstate&(KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) !=
      (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) )
    Curl_expire(data, 1); /* get this handle going again */

  return result;
}