static CURLcode smtp_state_auth_xoauth2_resp(struct connectdata *conn,
                                             int smtpcode, smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *xoauth = NULL;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Access denied: %d", smtpcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_xoauth2_message(conn->data, conn->user,
                                              conn->xoauth2_bearer,
                                              &xoauth, &len);
    if(!result && xoauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", xoauth);

      if(!result)
        state(conn, SMTP_AUTH_FINAL);
    }
  }

  Curl_safefree(xoauth);

  return result;
}