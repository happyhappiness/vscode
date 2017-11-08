static CURLcode imap_state_auth_digest_resp_resp(struct connectdata *conn,
                                                 int imapcode,
                                                 imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Authentication failed: %d", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Send an empty response */
    result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", "");

    if(!result)
      state(conn, IMAP_AUTHENTICATE_FINAL);
  }

  return result;
}