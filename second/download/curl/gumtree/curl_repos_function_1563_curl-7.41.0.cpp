static CURLcode pop3_multi_statemach(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  if((conn->handler->flags & PROTOPT_SSL) && !pop3c->ssldone) {
    result = Curl_ssl_connect_nonblocking(conn, FIRSTSOCKET, &pop3c->ssldone);
    if(result || !pop3c->ssldone)
      return result;
  }

  result = Curl_pp_statemach(&pop3c->pp, FALSE);
  *done = (pop3c->state == POP3_STOP) ? TRUE : FALSE;

  return result;
}