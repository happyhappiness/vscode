static CURLcode imap_state_auth_plain_resp(struct connectdata *conn,
                                           int imapcode,
                                           imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *plainauth = NULL;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied. %c", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_plain_message(data, conn->user, conn->passwd,
                                            &plainauth, &len);
    if(!result && plainauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", plainauth);

      if(!result)
        state(conn, IMAP_AUTHENTICATE_FINAL);
    }
  }

  Curl_safefree(plainauth);

  return result;
}