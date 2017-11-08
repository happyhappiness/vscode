void Curl_gskit_close(struct connectdata *conn, int sockindex)
{
  struct Curl_easy *data = conn->data;
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->use)
    close_one(connssl, data);
}