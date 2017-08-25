static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
{
  size_t sbytes;
  ssize_t senddata;
  const char *mode = "octet";
  char *filename;
  char buf[64];
  struct SessionHandle *data = state->conn->data;
  CURLcode result = CURLE_OK;

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
      return result;
    }

    if(data->set.upload) {
      /* If we are uploading, send an WRQ */
      setpacketevent(&state->spacket, TFTP_EVENT_WRQ);
      state->conn->data->req.upload_fromhere =
        (char *)state->spacket.data+4;
      if(data->state.infilesize != -1)
        Curl_pgrsSetUploadSize(data, data->state.infilesize);
    }
    else {
      /* If we are downloading, send an RRQ */
      setpacketevent(&state->spacket, TFTP_EVENT_RRQ);
    }
    /* As RFC3617 describes the separator slash is not actually part of the
       file name so we skip the always-present first letter of the path
       string. */
    filename = curl_easy_unescape(data, &state->conn->data->state.path[1], 0,
                                  NULL);
    if(!filename)
      return CURLE_OUT_OF_MEMORY;

    snprintf((char *)state->spacket.data+2,
             state->blksize,
             "%s%c%s%c", filename, '\0',  mode, '\0');
    sbytes = 4 + strlen(filename) + strlen(mode);

    /* add tsize option */
    if(data->set.upload && (data->state.infilesize != -1))
      snprintf(buf, sizeof(buf), "%" CURL_FORMAT_CURL_OFF_T,
               data->state.infilesize);
    else
      strcpy(buf, "0"); /* the destination is large enough */

    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_TSIZE);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf);
    /* add blksize option */
    snprintf( buf, sizeof(buf), "%d", state->requested_blksize );
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_BLKSIZE);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf );

    /* add timeout option */
    snprintf( buf, sizeof(buf), "%d", state->retry_time);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes,
                              TFTP_OPTION_INTERVAL);
    sbytes += tftp_option_add(state, sbytes,
                              (char *)state->spacket.data+sbytes, buf );

    /* the typecase for the 3rd argument is mostly for systems that do
       not have a size_t argument, like older unixes that want an 'int' */
    senddata = sendto(state->sockfd, (void *)state->spacket.data,
                      (SEND_TYPE_ARG3)sbytes, 0,
                      state->conn->ip_addr->ai_addr,
                      state->conn->ip_addr->ai_addrlen);
    if(senddata != (ssize_t)sbytes) {
      failf(data, "%s", Curl_strerror(state->conn, SOCKERRNO));
    }
    free(filename);
    break;

  case TFTP_EVENT_OACK:
    if(data->set.upload) {
      result = tftp_connect_for_tx(state, event);
    }
    else {
      result = tftp_connect_for_rx(state, event);
    }
    break;

  case TFTP_EVENT_ACK: /* Connected for transmit */
    result = tftp_connect_for_tx(state, event);
    break;

  case TFTP_EVENT_DATA: /* Connected for receive */
    result = tftp_connect_for_rx(state, event);
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(state->conn->data, "tftp_send_first: internal error");
    break;
  }

  return result;
}