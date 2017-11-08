static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
{
  int sbytes;
  const char *mode = "octet";
  char *filename;
  struct SessionHandle *data = state->conn->data;
  CURLcode res = CURLE_OK;

  /* Set ascii mode if -B flag was used */
  if(data->set.prefer_ascii)
    mode = "netascii";

  switch(event) {

  case TFTP_EVENT_INIT:    /* Send the first packet out */
  case TFTP_EVENT_TIMEOUT: /* Resend the first packet out */
    /* Increment the retry counter, quit if over the limit */
    state->retries++;
    if(state->retries>state->retry_max) {
      state->error = TFTP_ERR_NORESPONSE;
      state->state = TFTP_STATE_FIN;
      return res;
    }

    if(data->set.upload) {
      /* If we are uploading, send an WRQ */
      setpacketevent(&state->spacket, TFTP_EVENT_WRQ);
      state->conn->data->req.upload_fromhere =
        (char *)&state->spacket.data[4];
      if(data->set.infilesize != -1)
        Curl_pgrsSetUploadSize(data, data->set.infilesize);
    }
    else {
      /* If we are downloading, send an RRQ */
      setpacketevent(&state->spacket, TFTP_EVENT_RRQ);
    }
    /* As RFC3617 describes the separator slash is not actually part of the
    file name so we skip the always-present first letter of the path string. */
    filename = curl_easy_unescape(data, &state->conn->data->state.path[1], 0,
                                  NULL);
    if(!filename)
      return CURLE_OUT_OF_MEMORY;

    snprintf((char *)&state->spacket.data[2],
             TFTP_BLOCKSIZE,
             "%s%c%s%c", filename, '\0',  mode, '\0');
    sbytes = 4 + (int)strlen(filename) + (int)strlen(mode);
    sbytes = sendto(state->sockfd, (void *)&state->spacket,
                    sbytes, 0,
                    state->conn->ip_addr->ai_addr,
                    state->conn->ip_addr->ai_addrlen);
    if(sbytes < 0) {
      failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
    }
    Curl_safefree(filename);
    break;

  case TFTP_EVENT_ACK: /* Connected for transmit */
    infof(data, "%s\n", "Connected for transmit");
    state->state = TFTP_STATE_TX;
    res = tftp_set_timeouts(state);
    if(res)
      break;
    return tftp_tx(state, event);

  case TFTP_EVENT_DATA: /* connected for receive */
    infof(data, "%s\n", "Connected for receive");
    state->state = TFTP_STATE_RX;
    res = tftp_set_timeouts(state);
    if(res)
      break;
    return tftp_rx(state, event);

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(state->conn->data, "tftp_send_first: internal error");
    break;
  }
  return res;
}