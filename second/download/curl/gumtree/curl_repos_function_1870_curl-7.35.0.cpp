static CURLcode smtp_state_auth_digest_resp_resp(struct connectdata *conn,
                                                 int smtpcode,
                                                 smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Authentication failed: %d", smtpcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Send an empty response */
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", "");

    if(!result)
      state(conn, SMTP_AUTH_FINAL);
  }

  return result;
}