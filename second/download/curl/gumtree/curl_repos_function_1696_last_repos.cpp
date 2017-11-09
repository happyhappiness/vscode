static CURLcode pop3_state_user_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied. %c", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else
    /* Send the PASS command */
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "PASS %s",
                           conn->passwd ? conn->passwd : "");
  if(!result)
    state(conn, POP3_PASS);

  return result;
}