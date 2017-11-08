static void tftp_tx(tftp_state_data_t *state, tftp_event_t event)
{
  struct SessionHandle *data = state->conn->data;
  int sbytes;
  int rblock;

  switch(event) {

  case TFTP_EVENT_ACK:
    /* Ack the packet */
    rblock = ntohs(state->rpacket.u.data.block);

    if(rblock != state->block) {
      /* This isn't the expected block.  Log it and up the retry counter */
      infof(data, "Received ACK for block %d, expecting %d\n",
            rblock, state->block);
      state->retries++;
      /* Bail out if over the maximum */
      if(state->retries>state->retry_max) {
        failf(data, "%s\n",
              "tftp_tx: giving up waiting for block %d ack",
              state->block);
      }
      return;
    }
    /* This is the expected packet.  Reset the counters and send the next
       block */
    state->block++;
    state->retries = 0;
    state->spacket.event = htons(TFTP_EVENT_DATA);
    state->spacket.u.ack.block = htons(state->block);
    if(state->block > 1 && state->sbytes < 512) {
      state->state = TFTP_STATE_FIN;
      return;
    }
    Curl_fillreadbuffer(state->conn, 512, &state->sbytes);
    sbytes = sendto(state->sockfd, &state->spacket,
                    4+state->sbytes, MSG_NOSIGNAL,
                    &state->remote_addr, state->remote_addrlen);
    /* Check all sbytes were sent */
    if(sbytes<0) {
      failf(data, "%s\n", strerror(errno));
    }
    break;

  case TFTP_EVENT_TIMEOUT:
    /* Increment the retry counter and log the timeout */
    state->retries++;
    infof(data, "Timeout waiting for block %d ACK. "
          " Retries = %d\n", state->retries);
    /* Decide if we've had enough */
    if(state->retries > state->retry_max) {
      state->error = TFTP_ERR_TIMEOUT;
      state->state = TFTP_STATE_FIN;
    } else {
      /* Re-send the data packet */
      sbytes = sendto(state->sockfd, &state->spacket,
                      4+state->sbytes, MSG_NOSIGNAL,
                      &state->remote_addr, state->remote_addrlen);
      /* Check all sbytes were sent */
      if(sbytes<0) {
        failf(data, "%s\n", strerror(errno));
      }
    }
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(data, "%s\n", "tftp_tx: internal error");
    break;
  }

  /* Update the progress meter */
  Curl_pgrsSetUploadCounter(data, (curl_off_t) state->block*512);
}