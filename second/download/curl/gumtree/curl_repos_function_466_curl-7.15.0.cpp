static void tftp_rx(tftp_state_data_t *state, tftp_event_t event)
{
  int sbytes;
  int rblock;
  struct SessionHandle *data = state->conn->data;

  switch(event) {

  case TFTP_EVENT_DATA:

    /* Is this the block we expect? */
    rblock = ntohs(state->rpacket.u.data.block);
    if ((state->block+1) != rblock) {
      /* No, log it, up the retry count and fail if over the limit */
      infof(data,
            "Received unexpected DATA packet block %d\n", rblock);
      state->retries++;
      if (state->retries>state->retry_max) {
        failf(data, "tftp_rx: giving up waiting for block %d\n",
              state->block+1);
        return;
      }
    }
    /* This is the expected block.  Reset counters and ACK it. */
    state->block = rblock;
    state->retries = 0;
    state->spacket.event = htons(TFTP_EVENT_ACK);
    state->spacket.u.ack.block = htons(state->block);
    sbytes = sendto(state->sockfd, &state->spacket, 4, MSG_NOSIGNAL,
                    &state->remote_addr, state->remote_addrlen);
    if(sbytes < 0) {
      failf(data, "%s\n", strerror(errno));
    }

    /* Check if completed (That is, a less than full packet is recieved) */
    if (state->rbytes < (int)sizeof(state->spacket)){
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
    } else {
      /* Resend the previous ACK */
      sbytes = sendto(state->sockfd, &state->spacket,
                      4, MSG_NOSIGNAL,
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
    failf(data, "%s\n", "tftp_rx: internal error");
    break;
  }
  Curl_pgrsSetDownloadCounter(data,
                              (curl_off_t) state->block*512);
}