static CURLcode pop3_block_statemach(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  while(pop3c->state != POP3_STOP && !result)
    result = Curl_pp_statemach(&pop3c->pp, TRUE);

  return result;
}