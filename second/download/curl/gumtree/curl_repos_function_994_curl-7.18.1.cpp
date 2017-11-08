void Curl_nss_close(struct connectdata *conn, int sockindex)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->handle) {
    PR_Close(connssl->handle);
    if(connssl->client_nickname != NULL) {
      free(connssl->client_nickname);
      connssl->client_nickname = NULL;
    }
    connssl->handle = NULL;
  }
}