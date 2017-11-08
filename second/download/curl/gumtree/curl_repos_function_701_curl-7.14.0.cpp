void Curl_gtls_close(struct connectdata *conn)
{
  if(conn->ssl[0].use)
    close_one(conn, 0);
  if(conn->ssl[1].use)
    close_one(conn, 1);
}