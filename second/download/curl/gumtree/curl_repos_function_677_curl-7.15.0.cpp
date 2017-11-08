CURLcode Curl_is_resolved(struct connectdata *conn,
                          struct Curl_dns_entry **dns)
{
  (void)conn;
  *dns = NULL;

  return CURLE_COULDNT_RESOLVE_HOST;
}