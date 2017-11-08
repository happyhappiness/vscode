static void tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
{
  int sbytes;
  const char *mode = "octet";
  char *filename = state->conn->path;
  struct SessionHandle *data = state->conn->data;

  /* Set ascii mode if -B flag was used */
  if(data->set.ftp_ascii)
    mode = "netascii";

  switch(event) {

  case TFTP_EVENT_INIT:    /* Send the first packet out */
  case TFTP_EVENT_TIMEOUT: /* Resend the first packet out */
    /* Increment the retry counter, quit if over the limit */
    state->retries++;
    if(state->retries>state->retry_max) {
      state->error = TFTP_ERR_NORESPONSE;
      state->state = TFTP_STATE_FIN;
      return;
    }

    if(data->set.upload) {
      /* If we are uploading, send an WRQ */
      state->spacket.event = htons(TFTP_EVENT_WRQ);
      filename = curl_unescape(filename, strlen(filename));
      state->conn->upload_fromhere = (char *)state->spacket.u.data.data;
      if(data->set.infilesize != -1) {
        Curl_pgrsSetUploadSize(data, data->set.infilesize);
      }
    }
    else {
      /* If we are downloading, send an RRQ */
      state->spacket.event = htons(TFTP_EVENT_RRQ);
    }
    sprintf((char *)state->spacket.u.request.data, "%s%c%s%c",
            filename, '\0',  mode, '\0');
    sbytes = 4 + strlen(filename) + strlen(mode);
    sbytes = sendto(state->sockfd, &state->spacket, sbytes, 0,
                    state->conn->ip_addr->ai_addr,
                    state->conn->ip_addr->ai_addrlen);
    if(sbytes < 0) {
      failf(data, "%s\n", strerror(errno));
    }
    break;

  case TFTP_EVENT_ACK: /* Connected for transmit */
    infof(data, "%s\n", "Connected for transmit");
    state->state = TFTP_STATE_TX;
    tftp_set_timeouts(state);
    tftp_tx(state, event);
    break;

  case TFTP_EVENT_DATA: /* connected for receive */
    infof(data, "%s\n", "Connected for receive");
    state->state = TFTP_STATE_RX;
    tftp_set_timeouts(state);
    tftp_rx(state, event);
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(state->conn->data, "tftp_send_first: internal error\n");
    break;
  }
}