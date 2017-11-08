static CURLcode tftp_connect_for_tx(tftp_state_data_t *state,
                                    tftp_event_t event)
{
  CURLcode res;
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  struct SessionHandle *data = state->conn->data;

  infof(data, "%s\n", "Connected for transmit");
#endif
  state->state = TFTP_STATE_TX;
  res = tftp_set_timeouts(state);
  if(res != CURLE_OK)
    return(res);
  return tftp_tx(state, event);
}