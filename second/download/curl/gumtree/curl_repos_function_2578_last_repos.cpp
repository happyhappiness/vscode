int Curl_ssl_check_cxn(struct connectdata *conn)
{
  return Curl_ssl->check_cxn(conn);
}