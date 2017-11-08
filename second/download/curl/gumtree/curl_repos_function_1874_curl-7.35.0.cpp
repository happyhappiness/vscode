static CURLcode smtp_state_auth_cancel_resp(struct connectdata *conn,
                                            int smtpcode,
                                            smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  smtpstate state1 = SMTP_STOP;
  smtpstate state2 = SMTP_STOP;

  (void)smtpcode;
  (void)instate; /* no use for this yet */

  /* Remove the offending mechanism from the supported list */
  smtpc->authmechs ^= smtpc->authused;

  /* Calculate alternative SASL login details */
  result = smtp_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    /* Do we have any mechanisms left? */
    if(mech) {
      /* Retry SASL based authentication */
      result = smtp_perform_auth(conn, mech, initresp, len, state1, state2);

      Curl_safefree(initresp);
    }
    else {
      failf(data, "Authentication cancelled");

      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}