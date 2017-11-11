static CURLcode imap_state_auth_ntlm_type2msg_resp(struct connectdata *conn,
                                                   int imapcode,
                                                   imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *type2msg = NULL;
  char *type3msg = NULL;
  size_t len = 0;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied: %d", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Get the challenge message */
    imap_get_message(data->state.buffer, &type2msg);

    /* Decode the type-2 message */
    result = Curl_sasl_decode_ntlm_type2_message(data, type2msg, &conn->ntlm);
    if(result) {
      /* Send the cancellation */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", "*");

      if(!result)
        state(conn, IMAP_AUTHENTICATE_CANCEL);
    }
    else {
      /* Create the type-3 message */
      result = Curl_sasl_create_ntlm_type3_message(data, conn->user,
                                                   conn->passwd, &conn->ntlm,
                                                   &type3msg, &len);
      if(!result && type3msg) {
        /* Send the message */
        result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", type3msg);

        if(!result)
          state(conn, IMAP_AUTHENTICATE_FINAL);
      }
    }
  }

  Curl_safefree(type3msg);

  return result;
}