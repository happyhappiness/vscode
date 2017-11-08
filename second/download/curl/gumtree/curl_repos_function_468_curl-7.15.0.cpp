static CURLcode tftp_state_machine(tftp_state_data_t *state,
                                   tftp_event_t event)
{
  struct SessionHandle *data = state->conn->data;
  switch(state->state) {
  case TFTP_STATE_START:
    DEBUGF(infof(data, "TFTP_STATE_START\n"));
    tftp_send_first(state, event);
    break;
  case TFTP_STATE_RX:
    DEBUGF(infof(data, "TFTP_STATE_RX\n"));
    tftp_rx(state, event);
    break;
  case TFTP_STATE_TX:
    DEBUGF(infof(data, "TFTP_STATE_TX\n"));
    tftp_tx(state, event);
    break;
  case TFTP_STATE_FIN:
    infof(data, "%s\n", "TFTP finished");
    break;
  default:
    DEBUGF(infof(data, "STATE: %d\n", state->state));
    failf(data, "%s\n", "Internal state machine error");
    break;
  }
  return CURLE_OK;
}