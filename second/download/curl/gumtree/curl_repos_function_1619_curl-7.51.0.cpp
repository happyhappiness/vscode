static CURLcode pop3_state_apop_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Authentication failed: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* End of connect phase */
    state(conn, POP3_STOP);

  return result;
}