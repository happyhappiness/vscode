static CURLcode imap_state_auth_cram_resp(struct connectdata *conn,
                                          int imapcode,
                                          imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *chlg = NULL;
  char *chlg64 = NULL;
  char *rplyb64 = NULL;
  size_t len = 0;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied: %d", imapcode);
    return CURLE_LOGIN_DENIED;
  }

  /* Get the challenge message */
  imap_get_message(data->state.buffer, &chlg64);

  /* Decode the challenge message */
  result = Curl_sasl_decode_cram_md5_message(chlg64, &chlg, &len);
  if(result) {
    /* Send the cancellation */
    result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", "*");

    if(!result)
      state(conn, IMAP_AUTHENTICATE_CANCEL);
  }
  else {
    /* Create the response message */
    result = Curl_sasl_create_cram_md5_message(data, chlg, conn->user,
                                               conn->passwd, &rplyb64, &len);
    if(!result && rplyb64) {
      /* Send the response */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", rplyb64);

      if(!result)
        state(conn, IMAP_AUTHENTICATE_FINAL);
    }
  }

  Curl_safefree(chlg);
  Curl_safefree(rplyb64);

  return result;
}