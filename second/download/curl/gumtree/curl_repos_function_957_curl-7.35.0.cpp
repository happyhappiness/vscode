static CURLcode imap_state_auth_digest_resp(struct connectdata *conn,
                                            int imapcode,
                                            imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *chlg64 = NULL;
  char *rplyb64 = NULL;
  size_t len = 0;

  char nonce[64];
  char realm[128];
  char algorithm[64];

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied: %d", imapcode);
    return CURLE_LOGIN_DENIED;
  }

  /* Get the challenge message */
  imap_get_message(data->state.buffer, &chlg64);

  /* Decode the challange message */
  result = Curl_sasl_decode_digest_md5_message(chlg64, nonce, sizeof(nonce),
                                               realm, sizeof(realm),
                                               algorithm, sizeof(algorithm));
  if(result || strcmp(algorithm, "md5-sess") != 0) {
    /* Send the cancellation */
    result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", "*");

    if(!result)
      state(conn, IMAP_AUTHENTICATE_CANCEL);
  }
  else {
    /* Create the response message */
    result = Curl_sasl_create_digest_md5_message(data, nonce, realm,
                                                 conn->user, conn->passwd,
                                                 "imap", &rplyb64, &len);
    if(!result && rplyb64) {
      /* Send the response */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", rplyb64);

      if(!result)
        state(conn, IMAP_AUTHENTICATE_DIGESTMD5_RESP);
    }
  }

  Curl_safefree(rplyb64);

  return result;
}