{
  struct SingleRequest *k = &data->req;
  CURLcode result = CURLE_OK;

  /* first switch off both pause bits */
  int newstate = k->keepon &~ (KEEP_RECV_PAUSE| KEEP_SEND_PAUSE);

  /* set the new desired pause bits */
  newstate |= ((action & CURLPAUSE_RECV)?KEEP_RECV_PAUSE:0) |
    ((action & CURLPAUSE_SEND)?KEEP_SEND_PAUSE:0);

  /* put it back in the keepon */
  k->keepon = newstate;

  if(!(newstate & KEEP_RECV_PAUSE) && data->state.tempcount) {
    /* there are buffers for sending that can be delivered as the receive
       pausing is lifted! */
    unsigned int i;
    unsigned int count = data->state.tempcount;
    struct tempbuf writebuf[3]; /* there can only be three */

    /* copy the structs to allow for immediate re-pausing */
    for(i=0; i < data->state.tempcount; i++) {
      writebuf[i] = data->state.tempwrite[i];
      data->state.tempwrite[i].buf = NULL;
    }
    data->state.tempcount = 0;

    for(i=0; i < count; i++) {
      /* even if one function returns error, this loops through and frees all
         buffers */
      if(!result)
        result = Curl_client_chop_write(data->easy_conn,
                                        writebuf[i].type,
                                        writebuf[i].buf,
                                        writebuf[i].len);
      free(writebuf[i].buf);
    }
    if(result)
      return result;
  }

  /* if there's no error and we're not pausing both directions, we want
     to have this handle checked soon */
  if(!result &&
     ((newstate&(KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) !=
      (KEEP_RECV_PAUSE|KEEP_SEND_PAUSE)) )
    Curl_expire(data, 0, EXPIRE_RUN_NOW); /* get this handle going again */

  return result;
}