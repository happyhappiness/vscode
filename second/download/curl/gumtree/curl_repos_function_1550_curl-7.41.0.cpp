static CURLcode pop3_continue_auth(struct connectdata *conn,
                                   const char *resp)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  return Curl_pp_sendf(&pop3c->pp, "%s", resp);
}