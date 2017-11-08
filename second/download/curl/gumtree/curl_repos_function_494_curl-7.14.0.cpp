Curl_addrinfo *Curl_addrinfo_copy(void *org, int port)
{
  struct hostent *orig = org;

  return Curl_he2ai(orig, port);
}