static CURLcode pop3_connect(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  *done = FALSE; /* default to not done yet */

  /* We always support persistent connections in POP3 */
  connkeep(conn, "POP3 default");

  /* Set the default response time-out */
  pp->response_time = RESP_TIMEOUT;
  pp->statemach_act = pop3_statemach_act;
  pp->endofresp = pop3_endofresp;
  pp->conn = conn;

  /* Set the default preferred authentication type and mechanism */
  pop3c->preftype = POP3_TYPE_ANY;
  Curl_sasl_init(&pop3c->sasl, &saslpop3);

  /* Initialise the pingpong layer */
  Curl_pp_init(pp);

  /* Parse the URL options */
  result = pop3_parse_url_options(conn);
  if(result)
    return result;

  /* Start off waiting for the server greeting response */
  state(conn, POP3_SERVERGREET);

  result = pop3_multi_statemach(conn, done);

  return result;
}