Curl_addrinfo *Curl_addrinfo_copy(const void *orig, int port)
{
  (void) port;
  return (Curl_addrinfo*)orig;
}