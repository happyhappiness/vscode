static CURLcode pop3_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to. */

  /* The POP3 session may or may not have been allocated/setup at this
     point! */
  if(!dead_connection && pop3c->pp.conn && pop3c->pp.conn->bits.protoconnstart)
    if(!pop3_perform_quit(conn))
      (void)pop3_block_statemach(conn); /* ignore errors on QUIT */

  /* Disconnect from the server */
  Curl_pp_disconnect(&pop3c->pp);

  /* Cleanup the SASL module */
  Curl_sasl_cleanup(conn, pop3c->sasl.authused);

  /* Cleanup our connection based variables */
  Curl_safefree(pop3c->apoptimestamp);

  return CURLE_OK;
}