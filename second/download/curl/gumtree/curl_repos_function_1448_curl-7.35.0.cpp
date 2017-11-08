static CURLcode pop3_state_auth_digest_resp_resp(struct connectdata *conn,
                                                 int pop3code,
                                                 pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Authentication failed: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Send an empty response */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "");

    if(!result)
      state(conn, POP3_AUTH_FINAL);
  }

  return result;
}