struct Curl_dns_entry *
Curl_fetch_addr(struct connectdata *conn,
                const char *hostname,
                int port)
{
  struct Curl_easy *data = conn->data;
  struct Curl_dns_entry *dns = NULL;

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  dns = fetch_addr(conn, hostname, port);

  if(dns)
    dns->inuse++; /* we use it! */

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

  return dns;
}