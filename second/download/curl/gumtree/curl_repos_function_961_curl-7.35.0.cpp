static CURLcode imap_state_auth_xoauth2_resp(struct connectdata *conn,
                                             int imapcode,
                                             imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *xoauth = NULL;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied: %d", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_xoauth2_message(conn->data, conn->user,
                                              conn->xoauth2_bearer,
                                              &xoauth, &len);
    if(!result && xoauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", xoauth);

      if(!result)
        state(conn, IMAP_AUTHENTICATE_FINAL);
    }
  }

  Curl_safefree(xoauth);

  return result;
}