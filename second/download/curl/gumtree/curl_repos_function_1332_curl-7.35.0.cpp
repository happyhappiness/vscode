static CURLcode tftp_do(struct connectdata *conn, bool *done)
{
  tftp_state_data_t     *state;
  CURLcode              code;

  *done = FALSE;

  if(!conn->proto.tftpc) {
    code = tftp_connect(conn, done);
    if(code)
      return code;
  }
  state = (tftp_state_data_t *)conn->proto.tftpc;

  code = tftp_perform(conn, done);

  /* If tftp_perform() returned an error, use that for return code. If it
     was OK, see if tftp_translate_code() has an error. */
  if(code == CURLE_OK)
    /* If we have encountered an internal tftp error, translate it. */
    code = tftp_translate_code(state->error);

  return code;
}