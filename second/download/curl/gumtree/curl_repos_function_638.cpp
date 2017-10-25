CURLcode Curl_wait_for_resolv(struct connectdata *conn,
                              struct Curl_dns_entry **entry)
{
  (void)conn;
  *entry=NULL;
  return CURLE_COULDNT_RESOLVE_HOST;
}