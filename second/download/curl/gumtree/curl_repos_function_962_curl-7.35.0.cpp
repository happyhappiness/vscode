static CURLcode imap_state_auth_cancel_resp(struct connectdata *conn,
                                            int imapcode,
                                            imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct imap_conn *imapc = &conn->proto.imapc;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  imapstate state1 = IMAP_STOP;
  imapstate state2 = IMAP_STOP;

  (void)imapcode;
  (void)instate; /* no use for this yet */

  /* Remove the offending mechanism from the supported list */
  imapc->authmechs ^= imapc->authused;

  /* Calculate alternative SASL login details */
  result = imap_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    /* Do we have any mechanisms left or can we fallback to clear text? */
    if(mech) {
      /* Retry SASL based authentication */
      result = imap_perform_authenticate(conn, mech, initresp, state1, state2);

      Curl_safefree(initresp);
    }
    else if((!imapc->login_disabled) &&
            (imapc->preftype & IMAP_TYPE_CLEARTEXT))
      /* Perform clear text authentication */
      result = imap_perform_login(conn);
    else {
      failf(data, "Authentication cancelled");

      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}