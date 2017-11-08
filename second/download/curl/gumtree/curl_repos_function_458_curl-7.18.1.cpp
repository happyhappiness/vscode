void Curl_qsossl_close(struct connectdata *conn, int sockindex)

{
  struct SessionHandle *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->use)
    (void) Curl_qsossl_close_one(connssl, data);
}