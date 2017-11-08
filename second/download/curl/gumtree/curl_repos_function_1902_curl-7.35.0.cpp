bool Curl_ipvalid(struct connectdata *conn)
{
  if(conn->ip_version == CURL_IPRESOLVE_V6)
    return Curl_ipv6works();
  return TRUE;
}