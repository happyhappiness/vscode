static void pop3_to_pop3s(struct connectdata *conn)
{
  conn->handler = &Curl_handler_pop3s;
}