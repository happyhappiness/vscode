static CURLcode tftp_multi_statemach(struct connectdata *conn, bool *done)
{
  int                   rc;
  tftp_event_t          event;
  CURLcode              result = CURLE_OK;
  struct Curl_easy  *data = conn->data;
  tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;
  long                  timeout_ms = tftp_state_timeout(conn, &event);

  *done = FALSE;

  if(timeout_ms <= 0) {
    failf(data, "TFTP response timeout");
    return CURLE_OPERATION_TIMEDOUT;
  }
  if(event != TFTP_EVENT_NONE) {
    result = tftp_state_machine(state, event);
    if(result)
      return result;
    *done = (state->state == TFTP_STATE_FIN) ? TRUE : FALSE;
    if(*done)
      /* Tell curl we're done */
      Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  }
  else {
    /* no timeouts to handle, check our socket */
    rc = SOCKET_READABLE(state->sockfd, 0);

    if(rc == -1) {
      /* bail out */
      int error = SOCKERRNO;
      failf(data, "%s", Curl_strerror(conn, error));
      state->event = TFTP_EVENT_ERROR;
    }
    else if(rc != 0) {
      result = tftp_receive_packet(conn);
      if(result)
        return result;
      result = tftp_state_machine(state, state->event);
      if(result)
        return result;
      *done = (state->state == TFTP_STATE_FIN) ? TRUE : FALSE;
      if(*done)
        /* Tell curl we're done */
        Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
    }
    /* if rc == 0, then select() timed out */
  }

  return result;
}