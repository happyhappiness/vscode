static void smtp_to_smtps(struct connectdata *conn)
{
  conn->handler = &Curl_handler_smtps;
}