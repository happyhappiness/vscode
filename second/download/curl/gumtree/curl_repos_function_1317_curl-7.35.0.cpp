static CURLcode tftp_connect_for_rx(tftp_state_data_t *state,
                                    tftp_event_t event)
{
  CURLcode res;
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  struct SessionHandle *data = state->conn->data;

  infof(data, "%s\n", "Connected for receive");
#endif
  state->state = TFTP_STATE_RX;
  res = tftp_set_timeouts(state);
  if(res != CURLE_OK)
    return(res);
  return tftp_rx(state, event);
}