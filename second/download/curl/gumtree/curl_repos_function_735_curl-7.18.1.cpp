static CURLcode tftp_rx(tftp_state_data_t *state, tftp_event_t event)
{
  int sbytes;
  int rblock;
  struct SessionHandle *data = state->conn->data;

  switch(event) {

  case TFTP_EVENT_DATA:

    /* Is this the block we expect? */
    rblock = getrpacketblock(&state->rpacket);
    if((state->block+1) != rblock) {
      /* No, log it, up the retry count and fail if over the limit */
      infof(data,
            "Received unexpected DATA packet block %d\n", rblock);
      state->retries++;
      if(state->retries>state->retry_max) {
        failf(data, "tftp_rx: giving up waiting for block %d",
              state->block+1);
        return CURLE_TFTP_ILLEGAL;
      }
    }
    /* This is the expected block.  Reset counters and ACK it. */
    state->block = (unsigned short)rblock;
    state->retries = 0;
    setpacketevent(&state->spacket, TFTP_EVENT_ACK);
    setpacketblock(&state->spacket, state->block);
    sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                    4, SEND_4TH_ARG,
                    (struct sockaddr *)&state->remote_addr,
                    state->remote_addrlen);
    if(sbytes < 0) {
      failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
      return CURLE_SEND_ERROR;
    }

    /* Check if completed (That is, a less than full packet is received) */
    if(state->rbytes < (int)sizeof(state->spacket)){
      state->state = TFTP_STATE_FIN;
    }
    else {
      state->state = TFTP_STATE_RX;
    }
    break;

  case TFTP_EVENT_TIMEOUT:
    /* Increment the retry count and fail if over the limit */
    state->retries++;
    infof(data,
          "Timeout waiting for block %d ACK.  Retries = %d\n", state->retries);
    if(state->retries > state->retry_max) {
      state->error = TFTP_ERR_TIMEOUT;
      state->state = TFTP_STATE_FIN;
    }
    else {
      /* Resend the previous ACK */
      sbytes = sendto(state->sockfd, (void *)&state->spacket,
                      4, SEND_4TH_ARG,
                      (struct sockaddr *)&state->remote_addr,
                      state->remote_addrlen);
      /* Check all sbytes were sent */
      if(sbytes<0) {
        failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
        return CURLE_SEND_ERROR;
      }
    }
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(data, "%s", "tftp_rx: internal error");
    return CURLE_TFTP_ILLEGAL; /* not really the perfect return code for
                                  this */
  }
  return CURLE_OK;
}