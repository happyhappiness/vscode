{
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