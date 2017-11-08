static void pop3_to_pop3s(struct connectdata *conn)
{
  /* Change the connection handler */
  conn->handler = &Curl_handler_pop3s;

  /* Set the connection's upgraded to TLS flag */
  conn->tls_upgraded = TRUE;
}