static CURLcode tftp_tx(tftp_state_data_t *state, tftp_event_t event)
{
  struct SessionHandle *data = state->conn->data;
  ssize_t sbytes;
  int rblock;
  CURLcode res = CURLE_OK;
  struct SingleRequest *k = &data->req;

  switch(event) {

  case TFTP_EVENT_ACK:
  case TFTP_EVENT_OACK:
    if(event == TFTP_EVENT_ACK) {
      /* Ack the packet */
      rblock = getrpacketblock(&state->rpacket);

      if(rblock != state->block &&
         /* There's a bug in tftpd-hpa that causes it to send us an ack for
          * 65535 when the block number wraps to 0. So when we're expecting
          * 0, also accept 65535. See
          * http://syslinux.zytor.com/archives/2010-September/015253.html
          * */
         !(state->block == 0 && rblock == 65535)) {
        /* This isn't the expected block.  Log it and up the retry counter */
        infof(data, "Received ACK for block %d, expecting %d\n",
              rblock, state->block);
        state->retries++;
        /* Bail out if over the maximum */
        if(state->retries>state->retry_max) {
          failf(data, "tftp_tx: giving up waiting for block %d ack",
                state->block);
          res = CURLE_SEND_ERROR;
        }
        else {
          /* Re-send the data packet */
          sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                          4+state->sbytes, SEND_4TH_ARG,
                          (struct sockaddr *)&state->remote_addr,
                          state->remote_addrlen);
          /* Check all sbytes were sent */
          if(sbytes<0) {
            failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
            res = CURLE_SEND_ERROR;
          }
        }
        return res;
      }
      /* This is the expected packet.  Reset the counters and send the next
         block */
      time(&state->rx_time);
      state->block++;
    }
    else
      state->block = 1; /* first data block is 1 when using OACK */

    state->retries = 0;
    setpacketevent(&state->spacket, TFTP_EVENT_DATA);
    setpacketblock(&state->spacket, state->block);
    if(state->block > 1 && state->sbytes < (int)state->blksize) {
      state->state = TFTP_STATE_FIN;
      return CURLE_OK;
    }
    res = Curl_fillreadbuffer(state->conn, state->blksize, &state->sbytes);
    if(res)
      return res;
    sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                    4+state->sbytes, SEND_4TH_ARG,
                    (struct sockaddr *)&state->remote_addr,
                    state->remote_addrlen);
    /* Check all sbytes were sent */
    if(sbytes<0) {
      failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
      return CURLE_SEND_ERROR;
    }
    /* Update the progress meter */
    k->writebytecount += state->sbytes;
    Curl_pgrsSetUploadCounter(data, k->writebytecount);
    break;

  case TFTP_EVENT_TIMEOUT:
    /* Increment the retry counter and log the timeout */
    state->retries++;
    infof(data, "Timeout waiting for block %d ACK. "
          " Retries = %d\n", NEXT_BLOCKNUM(state->block), state->retries);
    /* Decide if we've had enough */
    if(state->retries > state->retry_max) {
      state->error = TFTP_ERR_TIMEOUT;
      state->state = TFTP_STATE_FIN;
    }
    else {
      /* Re-send the data packet */
      sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                      4+state->sbytes, SEND_4TH_ARG,
                      (struct sockaddr *)&state->remote_addr,
                      state->remote_addrlen);
      /* Check all sbytes were sent */
      if(sbytes<0) {
        failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
        return CURLE_SEND_ERROR;
      }
      /* since this was a re-send, we remain at the still byte position */
      Curl_pgrsSetUploadCounter(data, k->writebytecount);
    }
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    setpacketevent(&state->spacket, TFTP_EVENT_ERROR);
    setpacketblock(&state->spacket, state->block);
    (void)sendto(state->sockfd, (void *)state->spacket.data, 4, SEND_4TH_ARG,
                 (struct sockaddr *)&state->remote_addr,
                 state->remote_addrlen);
    /* don't bother with the return code, but if the socket is still up we
     * should be a good TFTP client and let the server know we're done */
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(data, "tftp_tx: internal error, event: %i", (int)(event));
    break;
  }

  return res;
}