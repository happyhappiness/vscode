static CURLcode pop3_perform_auth(struct connectdata *conn,
                                  const char *mech,
                                  const char *initresp)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  if(initresp) {                                  /* AUTH <mech> ...<crlf> */
    /* Send the AUTH command with the initial response */
    result = Curl_pp_sendf(&pop3c->pp, "AUTH %s %s", mech, initresp);
  }
  else {
    /* Send the AUTH command */
    result = Curl_pp_sendf(&pop3c->pp, "AUTH %s", mech);
  }

  return result;
}